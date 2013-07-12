#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP
#include <string>
#include <vector>
#include <fstream>

typedef unsigned char u8;
typedef unsigned int u32;


struct ImageData {
    u32 width, height;
    bool alpha;
    std::vector<u8> bytes;
};

enum OpenMode {
    //  Open for reading only
    OM_Read = 0x1,
    //  Erases everything in the file
    OM_Write = 0x2,
    //  Keeps the content and allows modifying
    OM_Modify = 0x1 | 0x2,
    //  Keeps the content and append all write operations
    OM_Append = 0x4,
    //  Permits binary operations
    OM_Binary = 0x8
};

class Texture;

class FileStream
{
    public:
        FileStream();
        FileStream( const std::string& f, int mode = OM_Read );
        ~FileStream();

        void Open( const std::string& f, int mode = OM_Read );
        void Close();

        //  Seek is just the combination of SeekG and SeekP
        //  SeekG and SeekP do the same as std::stream::seekg and seekp
        void Seek( long pos, std::ios_base::seekdir dir = std::ios_base::cur );
        void SeekG( long pos, std::ios_base::seekdir dir = std::ios_base::cur );
        void SeekP( long pos, std::ios_base::seekdir dir = std::ios_base::cur );

        //  TellG and TellP do the same thing as std::stream::tellg and tellp
        long TellG();
        long TellP();

        //  Get total size of the file
        long GetSize();

        //  Go forward until we encounter 'target' 'nbr' times
        //  and place the cursor just before this char
        void LookFor( char target, int nbr );
        //  Read a single char
        char ReadChar();
        //  Read until the end of the line
        std::string ReadLine();
        //  Read a block of text
        std::string ReadText( u32 sz );
        //  Reads the whole file
        std::string ReadAll();
        //  Read a block binary data
        template< class T > std::vector<T> ReadBinary( u32 count ) {
            std::vector<T> buffer(count);
            if( stream.is_open() )
                stream.read( (char*)buffer.data(), count * sizeof(T) );
            return buffer;
        }


        //  Write a single char
        void WriteChar( char c );
        //  Write a block of text
        void WriteText( const std::string& str );
        //  Write a block of binary data
        void WriteBinary( const void* data, u32 sz );
        //  Flush the contents
        void Flush();



        //  Read a png file and return it as a byte array
        static ImageData ReadPng( const std::string& file );
        //  Dump a 2D array to a .pgm file (black and white)
        static void WriteToPPM( const std::string& file, const std::vector< std::vector< u8 > >& array );
        //  Returns the std::ios_base::openmode relative to the OpenMode
        static std::ios_base::openmode GetMode( int mode );
        //  Check if a file exists
        static bool Exists( const std::string& file );
        //  Create a file
        static void Create( const std::string& file );

    private:
        std::string file;
        std::fstream stream;
};

FileStream& operator<<( FileStream& fs, char c );
FileStream& operator<<( FileStream& fs, const std::string& str );
FileStream& operator<<( FileStream& fs, int i );
FileStream& operator<<( FileStream& fs, u32 i );
FileStream& operator<<( FileStream& fs, float f );

FileStream& operator>>( FileStream& fs, char& c );
FileStream& operator>>( FileStream& fs, std::string& str );
FileStream& operator>>( FileStream& fs, int& i );
FileStream& operator>>( FileStream& fs, u32& i );
FileStream& operator>>( FileStream& fs, float& f );

#endif // FILESTREAM_HPP
