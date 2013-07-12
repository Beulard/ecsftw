#ifndef SPRITEFACTORY_HPP
#define SPRITEFACTORY_HPP
#include "vec2.hpp"
#include <string>

typedef vec2i Pos;
typedef vec2ui Size;
typedef vec2ui TexCoord;
typedef unsigned int u32;

namespace SpriteFactory {

    void AttachSprite( u32 id, const std::string& batch, const Pos& pos, const Size& size, const TexCoord& topLeft, const TexCoord& bottomRight );
    void DetachSprite( u32 id );

}

#endif // SPRITEFACTORY_HPP
