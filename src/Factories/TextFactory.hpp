#ifndef TEXTFACTORY_HPP
#define TEXTFACTORY_HPP
#include <string>
#include "vec2.hpp"

typedef unsigned int u32;

namespace TextFactory {

    void AttachText( u32 id, const std::string& text, const std::string& batch, const vec2i& pos );
    void DetachText( u32 id );

}

#endif // TEXTFACTORY_HPP
