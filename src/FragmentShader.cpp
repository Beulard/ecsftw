#include "FragmentShader.hpp"
#include "Common.hpp"

FragmentShader::FragmentShader(){
    type = ST_Fragment;
}

FragmentShader::~FragmentShader(){
    if( id != 0 )
        glDeleteShader( id );
}

void FragmentShader::Load( const char* code ) {
     // Create the shaders
    id = glCreateShader( GL_FRAGMENT_SHADER );


    GLint result = GL_FALSE;
    int logLength;

    // Compile fragment shader
    Info( "Compiling fragment shader..." );
    glShaderSource( id, 1, &code, NULL );
    glCompileShader( id );

    // Check fragment shader
    glGetShaderiv( id, GL_COMPILE_STATUS, &result );
    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &logLength );
    if( result == GL_FALSE ) {
        char errorMsg[logLength];
        glGetShaderInfoLog( id, logLength, NULL, errorMsg );
        Error( errorMsg );
    }
    else
        Append( " Success" );
}
