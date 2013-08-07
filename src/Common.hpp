#ifndef WATER_COMMON
#define WATER_COMMON
#include <cstdio>
#include <string>

typedef unsigned char u8;
typedef unsigned int u32;

//  Game log
class Game;
extern Game game;
extern float projMatrix[9];

std::string IntToString( int i );
std::string FloatToString( float f );
int StringToInt( const std::string& str );



#if defined(_WIN32) || defined(__WIN32__)
	#define WATER_WINDOWS
#elif defined(linux) || defined(__linux)
	#define WATER_LINUX
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	#error OS not yet supported
	#define WATER_APPLE
#else
	#error OS not supported
#endif


#endif // WATER_COMMON
