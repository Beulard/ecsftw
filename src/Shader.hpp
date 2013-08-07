#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

enum ShaderType {
	ST_Vertex,
	ST_Fragment
};

class Shader
{
	public:
		Shader();
		~Shader();

		void Load( const char* code, ShaderType type );

		friend class ShaderProgram;

	protected :
		GLuint id;
		ShaderType type;
};

#endif // SHADER_HPP
