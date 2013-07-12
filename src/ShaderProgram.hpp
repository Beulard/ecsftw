#ifndef WATER_SHADERPROGRAM
#define WATER_SHADERPROGRAM
#include "VertexShader.hpp"
#include "FragmentShader.hpp"

class ShaderProgram
{
    public:
        ShaderProgram();
        ShaderProgram( VertexShader& pVS, FragmentShader& pFS );
        ~ShaderProgram();

        //  These functions do not link the shader after being used. Remember to do it manually
        void SetFS( FragmentShader* pFS );
        void SetVS( VertexShader* pVS );
        ////

        int GetUniformLocation( const char* s );

        void SetCameraUse( bool use );

        GLuint GetID()  const;

        //  Link the program with the shaders.
        void Link();
        //  Use the shader program for rendering.
        void Use();

        bool UsesCamera();

    private:
        VertexShader* vs;
        FragmentShader* fs;
        GLuint id;
        bool usesCamera;
};

#endif // WATER_SHADERPROGRAM
