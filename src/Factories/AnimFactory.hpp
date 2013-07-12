#ifndef ANIMFACTORY_HPP
#define ANIMFACTORY_HPP
#include <string>
#include <vector>
#include "vec2.hpp"

typedef vec2i Pos;
typedef vec2ui Size;
typedef vec2ui TexCoord;
typedef unsigned int u32;

struct FrameInfo {
    TexCoord topLeft, bottomRight;
    float time;
};

namespace AnimFactory {

    void AttachAnim( u32 id, const std::string& batch, const Pos& pos, const Size& sz, const std::vector<FrameInfo>& frames );
    void DetachAnim( u32 id );

}

#endif // ANIMFACTORY_HPP
