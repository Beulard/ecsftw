#include "ShaderProgram.hpp"
#include "Output.hpp"
#include "Common.hpp"
#include "Shader.hpp"

ShaderProgram::ShaderProgram() : vertex(NULL), fragment(NULL), id(0){

}

ShaderProgram::ShaderProgram( Shader& vs, Shader& fs ) : vertex(&vs), fragment(&fs), id(0){
	Link();
}

ShaderProgram::~ShaderProgram(){
	if( id != 0 )
		glDeleteProgram( id );
}

void ShaderProgram::SetVertex( Shader* vs ) {
	vertex = vs;
}

void ShaderProgram::SetFragment( Shader* fs ) {
	fragment = fs;
}

int ShaderProgram::GetUniformLocation( const char* s ) {
	return glGetUniformLocation( id, s );
}

void ShaderProgram::SetCameraUse( bool use ) {
	usesCamera = use;
}

void ShaderProgram::Link() {
	Info( "Linking shader program..." );
	if( id == 0 ) {
		if( vertex == NULL )
			Error( "Couldn't link shader program : vertex shader isn't set." );
		if( fragment == NULL )
			Error( "Couldn't link shader program : fragment shader isn't set." );
		id = glCreateProgram();
	}
	glAttachShader( id, vertex->id );
	glAttachShader( id, fragment->id );
	glLinkProgram( id );

	GLint result = GL_FALSE;

	glGetProgramiv( id, GL_LINK_STATUS, &result );
	if( result == GL_FALSE ) {
		int logLength;
		glGetProgramiv( id, GL_INFO_LOG_LENGTH, &logLength );
		char errorMsg[logLength];
		glGetProgramInfoLog( id, logLength, NULL, errorMsg );
		Error( errorMsg );
	}
	else
		Append( " Success" );
}

void ShaderProgram::Use() {
	glUseProgram( id );
}

bool ShaderProgram::UsesCamera() {
	return usesCamera;
}
