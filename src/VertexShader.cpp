#include "VertexShader.hpp"
#include "Common.hpp"

VertexShader::VertexShader(){
    type = ST_Vertex;
}

VertexShader::~VertexShader(){
    if( id != 0 )
        glDeleteShader( id );
}


void VertexShader::Load( const char* code ) {
    // Create the shaders
    id = glCreateShader( GL_VERTEX_SHADER );


    GLint result = GL_FALSE;
    int logLength = 0;

    // Compile Vertex Shader
    Info( "Compiling vertex shader..." );
    glShaderSource( id, 1, &code, NULL );
    glCompileShader( id );

    // Check Vertex Shader
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
