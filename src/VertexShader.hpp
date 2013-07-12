#ifndef WATER_VERTEXSHADER
#define WATER_VERTEXSHADER
#include "Shader.hpp"

class VertexShader : public Shader
{
    public:
        VertexShader();
        ~VertexShader();

        void Load( const char* code );

        friend class ShaderProgram;

};

#endif // WATER_VERTEXSHADER
