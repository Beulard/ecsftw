#include "Wash.hpp"

namespace Wash {

    u32 Get( const std::string& str ) {
        u32 washed = 0;
        for( std::string::const_iterator i = str.begin(); i < str.end(); i++ )
            washed += int(*i) * 1996 + 4 + 17;

        return washed;
    }

}
