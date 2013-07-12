#include "ShaderProgram.hpp"
#include "Common.hpp"

ShaderProgram::ShaderProgram() : vs(NULL), fs(NULL), id(0){

}

ShaderProgram::ShaderProgram( VertexShader& pVS, FragmentShader& pFS ) : vs(&pVS), fs(&pFS), id(0){
    Link();
}

ShaderProgram::~ShaderProgram(){
    if( id != 0 )
        glDeleteProgram( id );
    if( vs )
        delete vs;
    if( fs )
        delete fs;
}

void ShaderProgram::SetFS( FragmentShader* pFS ) {
    fs = pFS;
}

void ShaderProgram::SetVS( VertexShader* pVS ) {
    vs = pVS;
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
        if( vs == NULL )
            Error( "Couldn't link shader program : vertex shader isn't set." );
        if( fs == NULL )
            Error( "Couldn't link shader program : fragment shader isn't set." );
        id = glCreateProgram();
    }
    glAttachShader( id, vs->id );
    glAttachShader( id, fs->id );
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

GLuint ShaderProgram::GetID()   const {
    return id;
}

bool ShaderProgram::UsesCamera() {
    return usesCamera;
}
