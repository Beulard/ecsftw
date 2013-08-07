#include "ResourceManager.hpp"
#include "FileStream.hpp"
#include "Texture.hpp"
#include "Wash.hpp"
#include "Output.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include <map>
#include <cstring>

const char* GetExtension( const char* s ) {
	const char* lastDot = strrchr( s, '.' );
	return lastDot + 1;
}

char* RemoveExtension( char* s ) {
	char* lastDot = strrchr( s, '.' );
	lastDot[0] = '\0';
	return s;
}

bool streq( const char* s, const char* s2 ) {
	return (strcmp( s, s2 ) == 0 );
}

namespace ResourceManager {

	std::map< wash, Texture* > textures;
	std::map< wash, Shader* > shaders;
	std::map< wash, ShaderProgram* > shaderPrograms;
	char resFolder[] = "resources/";

	void LoadTexture( const char* file ) {
		wash id = Wash::Get( file );

		//	Get real path for the resource
		char realPath[strlen(resFolder) + strlen(file) + 2];
		strcpy( realPath, resFolder );
		strcat( realPath, file );
		realPath[strlen(resFolder) + strlen(file) + 1] = '\0';

		ImageData img = FileStream::ReadPng( realPath );
		auto t = textures.insert( std::pair< wash, Texture* >( id, new Texture ) ).first;
		t->second->Generate( img.bytes, vec2ui( img.width, img.height ), img.alpha );
	}

	void LoadShader( const char* file ) {
		wash id = Wash::Get(file);
		const char* ext = GetExtension( file );

		//	Get real path for the resource
		char realPath[strlen(resFolder) + strlen(file) + 2];
		strcpy( realPath, resFolder );
		strcat( realPath, file );
		realPath[strlen(resFolder) + strlen(file) + 1] = '\0';

		FileStream fs( realPath, OM_Read );
		std::string code = fs.ReadAll();
		Shader* s = new Shader;
		if( streq(ext, "vs") ) {
			Info( "Loading vertex shader %s", file );
			s->Load( code.c_str(), ST_Vertex );
		}
		else if( streq(ext, "fs") ) {
			Info( "Loading fragment shader %s", file );
			s->Load( code.c_str(), ST_Fragment );
		}
		else {
			Error( "File extension %s not recognized for shader %s : should be .vs or .fs", ext, file );
		}
		shaders.insert( std::pair< wash, Shader* >( id, s ) );
	}

	void LoadShaderProgram( const char* vertex, const char* fragment, ShaderCameraMode camera ) {
		char vertexCpy[strlen(vertex) + 1];
		strcpy( vertexCpy, vertex );
		vertexCpy[strlen(vertex)] = '\0';
		char* idStr = RemoveExtension( vertexCpy );
		wash id = Wash::Get( idStr );

		Shader* v = GetShader( vertex );
		Shader* f = GetShader( fragment );
		ShaderProgram* shader = new ShaderProgram;
		shader->SetVertex( v );
		shader->SetFragment( f );

		Info( "Loading shader program %s", idStr );
		shader->Link();
		shader->SetCameraUse( camera );

		shaderPrograms.insert( std::pair< wash, ShaderProgram* >( id, shader ) );
	}

	Texture* GetTexture( const char* name ) {
		wash id = Wash::Get( name );
		return textures[id];
	}

	Shader* GetShader( const char* name ) {
		wash id = Wash::Get( name );
		return shaders[id];
	}

	ShaderProgram* GetShaderProgram( const char* name ) {
		wash id = Wash::Get( name );
		return shaderPrograms[id];
	}

	void UnloadAll() {
		for( auto it = textures.begin(); it != textures.end(); it++ ) {
			it->second->Destroy();
		}
	}

}
