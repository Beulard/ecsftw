#ifndef WATER_SHADERPROGRAM
#define WATER_SHADERPROGRAM
#include "GL/glew.h"

class Shader;

class ShaderProgram
{
	public:
		ShaderProgram();
		ShaderProgram( Shader& vs, Shader& fs );
		~ShaderProgram();

		//  These functions do not link the shader after being used. Remember to do it manually
		void SetVertex( Shader* vs );
		void SetFragment( Shader* fs );
		////

		int GetUniformLocation( const char* s );

		void SetCameraUse( bool use );

		//  Link the program with the shaders.
		void Link();
		//  Use the shader program for rendering.
		void Use();

		bool UsesCamera();

	private:
		Shader* vertex;
		Shader* fragment;
		GLuint id;
		bool usesCamera;
};

#endif // WATER_SHADERPROGRAM
