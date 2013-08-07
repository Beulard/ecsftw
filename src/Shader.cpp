#include "Shader.hpp"
#include "Output.hpp"
#include "Common.hpp"

Shader::Shader(){

}

Shader::~Shader(){

}

void Shader::Load( const char* code, ShaderType type ) {
	GLint result = GL_FALSE;
	int logLength = 0;

	// Compile shader
	if( type == ST_Vertex ) {
		id = glCreateShader( GL_VERTEX_SHADER );
		Info( "Compiling vertex shader..." );
	}
	else {
		id = glCreateShader( GL_FRAGMENT_SHADER );
		Info( "Compiling fragment shader..." );
	}
	glShaderSource( id, 1, &code, NULL );
	glCompileShader( id );

	// Check shader
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

