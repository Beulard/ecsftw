#include "Common.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>


std::string IntToString( int i ) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::string FloatToString( float f ) {
    std::stringstream ss;
    ss << f;
    return ss.str();
}

int StringToInt( const std::string& str ) {
    return atoi( str.c_str() );
}
