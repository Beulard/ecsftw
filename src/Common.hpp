#ifndef WATER_COMMON
#define WATER_COMMON
#include <cstdio>
#include <string>

typedef unsigned char u8;
typedef unsigned int u32;

//  Game log
extern FILE* gamelog;
class Game;
extern Game game;
extern float projMatrix[9];

std::string IntToString( int i );
std::string FloatToString( float f );
int StringToInt( const std::string& str );


#define _Log(...) fprintf(gamelog, __VA_ARGS__)
#define _Csl(...) printf(__VA_ARGS__)

#define _InfoStr	"\n[INFO] : "
#define _WarningStr "\n[WARNING] : "
#define _ErrorStr	"\n[ERROR] : "

#define _TraceInfo "\n\nIn function %s from file %s at line %d :", __func__, __FILE__, __LINE__

#define _InfoLog(...)		_Log(_InfoStr); _Log(__VA_ARGS__);
#define _WarningLog(...)	_Log(_WarningStr); _Log(__VA_ARGS__);
#define _ErrorLog(...)		_Log(_TraceInfo); _Log(_ErrorStr); _Log(__VA_ARGS__);
#define _AppendLog(...)		_Log(__VA_ARGS__)

#define _InfoCsl(...)		_Csl(_InfoStr); _Csl(__VA_ARGS__);
#define _WarningCsl(...)	_Csl(_WarningStr); _Csl(__VA_ARGS__);
#define _ErrorCsl(...)		_Csl(_TraceInfo); _Csl(_ErrorStr); _Csl(__VA_ARGS__);

#define _AppendCsl(...)		_Csl(__VA_ARGS__)

#ifdef WATER_DEBUG
    #define Info(...)		do{_InfoLog(__VA_ARGS__);	_InfoCsl(__VA_ARGS__);} while(0);
    #define Warning(...)	do{_WarningLog(__VA_ARGS__);	_WarningCsl(__VA_ARGS__);} while(0);
    #define Error(...)		do{_ErrorCsl(__VA_ARGS__);	_ErrorLog(__VA_ARGS__);} while(0);
    #define Append(...)		do{_AppendLog(__VA_ARGS__);	_AppendCsl(__VA_ARGS__);} while(0);
#else
    #define Info(...)		_InfoLog(__VA_ARGS__)
    #define Warning(...)	_WarningLog(__VA_ARGS__)
    #define Error(...)		do{_ErrorLog(__VA_ARGS__);} while(0)
    #define Append(...)		_AppendLog(__VA_ARGS__)
#endif

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
