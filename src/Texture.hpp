#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "GL/glew.h"
#include <vector>
#include "vec2.hpp"

typedef unsigned char u8;

class ShaderProgram;
class Texture
{
    public:
        Texture();
        ~Texture();

        void Generate( const std::vector<u8>& bytes, const vec2ui& sz, bool rgba );
        void Destroy();

        void Bind();

        const vec2ui& GetSize() const;

    private:
        GLuint id;
        vec2ui size;
};

#endif // TEXTURE_HPP
