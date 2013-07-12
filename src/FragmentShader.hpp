#ifndef WATER_FRAGMENTSHADER
#define WATER_FRAGMENTSHADER
#include "Shader.hpp"

class FragmentShader : public Shader
{
    public:
        FragmentShader();
        ~FragmentShader();

        void Load( const char* code );

        friend class ShaderProgram;

};

#endif // WATER_FRAGMENTSHADER
