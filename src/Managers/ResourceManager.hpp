#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <string>

class Texture;
class ShaderProgram;
class Shader;

enum ShaderCameraMode {
	NoCamera = false,
	Camera = true
};

namespace ResourceManager {

	void LoadTexture( const char* file );
	void LoadShaderProgram( const char* vertex, const char* fragment, ShaderCameraMode camera );
	void LoadShader( const char* file );

	Texture* GetTexture( const char* name );
	ShaderProgram* GetShaderProgram( const char* name );
	Shader* GetShader( const char* name );

	void UnloadAll();

}

#endif // RESOURCEMANAGER_HPP
