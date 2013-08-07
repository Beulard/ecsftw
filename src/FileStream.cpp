#include "FileStream.hpp"
#include "Output.hpp"
#include "Common.hpp"
#include "png/png.h"

FileStream::FileStream() {

}

FileStream::FileStream( const char* file, int mode ) {
	Open( file, mode );
}

FileStream::~FileStream() {
	Close();
}

void FileStream::Open( const char* f, int mode ) {
	file = f;
	stream.open( f, GetMode(mode) );
	if( !stream.is_open() )
		Error( "Could not open file %s for reading", f );
}

void FileStream::Close() {
	if( stream.is_open() )
		stream.close();
}

void FileStream::Seek( long pos, std::ios_base::seekdir dir ) {
	SeekG( pos, dir );
	SeekP( pos, dir );
}

void FileStream::SeekG( long pos, std::ios_base::seekdir dir ) {
	if( stream.is_open() )
		stream.seekg( pos, dir );
}

void FileStream::SeekP( long pos, std::ios_base::seekdir dir ) {
	if( stream.is_open() )
		stream.seekp( pos, dir );
}

long FileStream::TellG() {
	if( stream.is_open() )
		return (long)stream.tellg();
	return 0;
}

long FileStream::TellP() {
	if( stream.is_open() )
		return (long)stream.tellp();
	return 0;
}

long FileStream::GetSize() {
	long ret = 0;
	if( stream.is_open() ) {
		long pos = TellG();
		Seek( 0, std::ios_base::end );
		ret = TellG();
		Seek( pos );
	}
	return ret;
}

void FileStream::LookFor( char target, int nbr ) {
	if( stream.is_open() ) {
		//  Repeat till we reached 'target' 'nbr' times
		for( int i = 0; i < nbr; ++i ) {
			for( char c = '\0'; c != target; ) {
				stream.get( c );
				if( stream.eof() ) {
					Warning( "Reached end of file '%s' when reading", file.c_str() );
					return;
				}
				if( !stream.good() ) {
					Warning( "Couldn't read file '%s'", file.c_str() );
					return;
				}
			}
		}
		SeekG( TellG() - 1 );
		SeekP( TellG() );
	}
}

char FileStream::ReadChar() {
	char c;
	stream.get( c );
	return c;
}

std::string FileStream::ReadLine() {
	long startpos = TellG();
	for( char c = 'a'; c != '\n' && c != '\0'; ) {
		c = ReadChar();
	}
	long endpos = TellG();
	//  Length of the whole line without the '\n' or the '\0' at the end
	long offset = endpos - startpos - 1;
	Seek( startpos );
	char buf[offset];
	stream.get( buf, offset );
	return std::string(buf);
}

std::string FileStream::ReadText( u32 sz ) {
	//  We need to add 1 to the size to put the ending '\0'
	char buf[sz + 1];
	stream.get( buf, sz );
	buf[sz] = '\0';
	return std::string(buf);
}

std::string FileStream::ReadAll() {
	if( !stream.is_open() ) {
		Warning( "Couldn't open file %s for input", file.c_str() );
		return std::string( "" );
	}
	SeekG( 0, std::ios::end );
	long length = TellG();
	SeekG( 0, std::ios::beg );
	char buffer[length + 1];
	memset( buffer, '\0', length + 1 );
	//  We zero the buffer because it can cause random shader compilation errors
	stream.read( buffer, length );

	std::string s( buffer );
	return s;
}

u32 FileStream::GetCount() {
	return stream.gcount();
}

void FileStream::WriteChar( char c ) {
	if( stream.is_open() )
		stream << c;
}

void FileStream::WriteText( const std::string& str ) {
	if( stream.is_open() )
		stream << str;
}

void FileStream::WriteBinary( const void* data, u32 sz ) {
	if( stream.is_open() )
		stream.write( (char*)data, sz );
}

void FileStream::Flush() {
	if( stream.is_open() )
		stream.flush();
}

ImageData FileStream::ReadPng( const std::string& file ) {
	FILE* f = NULL;
	f = fopen( file.c_str(), "rb" );
	if( !f )
		Error( "File '%s' does not exit !", file.c_str() );

	//  Check if the file is not an empty file
	if( ferror( f ) ) {
		fclose( f );
		Error( "Error in png header of file %s !", file.c_str() );
	}
	//  Check if there was a problem opening the file
	if( !f )
		Error( "Couldn't open file %s !", file.c_str() );
	png_byte pngsig[8];
	fread( (char*)pngsig, 8, 1, f );


	//  Check if the png signature is valid
	if( png_sig_cmp( pngsig, 0, 8 ) != 0 ) {
		fclose( f );
		Error( "File %s is not a valid png file !", file.c_str() );
	 }

	png_structp readStruct = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if( !readStruct ) {
		fclose( f );
		Error( "Error trying to create a png reading struct in %s !", file.c_str() );
	 }

	 png_infop infoStruct = png_create_info_struct( readStruct );
	 if( !infoStruct ) {
		png_destroy_read_struct( &readStruct, 0, 0 );
		fclose( f );
		Error( "Error trying to create a png info struct in file %s !", file.c_str() );
	 }

	ImageData img;
	png_bytepp rowPtrs = NULL;

	if( setjmp( png_jmpbuf( readStruct ) ) ) {
		png_destroy_read_struct( &readStruct, &infoStruct, 0 );
		if( rowPtrs )
			delete[] rowPtrs;
		fclose( f );
		Error( "An error has occured while reading %s !", file.c_str() );
	}

	png_init_io( readStruct, f );
	png_set_sig_bytes( readStruct, 8 );
	png_read_png( readStruct, infoStruct, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL );


	int bitdepth, interlace, colortype;
	png_get_IHDR( readStruct, infoStruct, &img.width, &img.height, &bitdepth, &colortype, &interlace, NULL, NULL );


	img.alpha = ( (colortype & PNG_COLOR_MASK_ALPHA) );

	u32 rowbytes = png_get_rowbytes( readStruct, infoStruct );
	img.bytes.resize( rowbytes * img.height );

	rowPtrs = png_get_rows( readStruct, infoStruct );

	for( u32 y = 0; y < img.height; ++y )
		memcpy( &img.bytes[0] + (rowbytes * (img.height - 1 - y)), rowPtrs[y], rowbytes );


	png_destroy_read_struct( &readStruct, &infoStruct, 0 );

	fclose( f );
	return img;
}

void FileStream::WriteToPPM( const std::string& file, const std::vector< std::vector< u8 > >& array ) {
	FileStream out( file.c_str(), OM_Write );
	u32 width = array.size(), height = array.back().size();

	out << "P5\n"
		<< array.size() << " " << array.back().size()
		<< "\n255\n";

	//  We need to invert the y coordinate because the map is generated
	//  top-to-bottom but the .pgm image must be written bottom-to-top
	for( int y = height - 1; y >= 0; --y )
		for( u32 x = 0; x < width; ++x )
			out.WriteBinary( &array[x][y], sizeof(u8) );

	out.Close();
}

std::ios_base::openmode FileStream::GetMode( int mode ) {
	std::ios_base::openmode m = std::ios::in;
	if( !(mode & OM_Read) )
		m ^= std::ios::in;
	if( mode & OM_Write )
		m ^= std::ios::out;
	if( mode & OM_Append )
		m ^= std::ios::app;
	if( mode & OM_Binary )
		m ^= std::ios::binary;
	return m;
}

bool FileStream::Exists( const std::string& file ) {
	std::ifstream stream( file.c_str() );
	if( stream.is_open() ) {
		stream.close();
		return true;
	}
	else
		return false;
}

void FileStream::Create( const std::string& file ) {
	std::ofstream stream( file.c_str() );
	stream.close();
}

FileStream& operator<<( FileStream& fs, char c ) {
	fs.WriteChar(c);
	return fs;
}

FileStream& operator<<( FileStream& fs, const std::string& s ) {
	fs.WriteText( s );
	return fs;
}

FileStream& operator<<( FileStream& fs, int i ) {
	fs.WriteText( IntToString(i) );
	return fs;
}

FileStream& operator<<( FileStream& fs, u32 i ) {
	fs.WriteText( IntToString(i) );
	return fs;
}

FileStream& operator<<( FileStream& fs, float f ) {
	fs.WriteText( FloatToString(f) );
	return fs;
}

FileStream& operator>>( FileStream& fs, char& c ) {
	c = fs.ReadChar();
	return fs;
}

FileStream& operator>>( FileStream& fs, std::string& s ) {
	s = fs.ReadAll();
	return fs;
}

FileStream& operator>>( FileStream& fs, int& i ) {
	i = fs.ReadBinary<int>(1).back();
	return fs;
}

FileStream& operator>>( FileStream& fs, u32& i ) {
	i = fs.ReadBinary<u32>(1).back();
	return fs;
}

FileStream& operator>>( FileStream& fs, float& f ) {
	f = fs.ReadBinary<float>(1).back();
	return fs;
}
