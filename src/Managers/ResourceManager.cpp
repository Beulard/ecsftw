#include "ResourceManager.hpp"
#include "FileStream.hpp"
#include "Texture.hpp"
#include "Wash.hpp"
#include "Common.hpp"
#include "ShaderProgram.hpp"
#include <map>

std::string RemoveExtension( const std::string& s ) {
    std::string path = s.substr( 0, s.find( "." ) );
    return path;
}

namespace ResourceManager {

    std::map< wash, Texture* > textures;
    std::map< wash, ShaderProgram* > shaders;

    void LoadTexture( const std::string& file ) {
        wash id = Wash::Get( file );
        ImageData img = FileStream::ReadPng( "resources/" + file );
        auto t = textures.insert( std::pair< wash, Texture* >( id, new Texture ) ).first;
        t->second->Generate( img.bytes, vec2ui( img.width, img.height ), img.alpha );
    }

    void LoadShader( const std::string& vertex, const std::string& fragment, bool camera ) {
        std::string idStr = RemoveExtension( vertex );
        wash id = Wash::Get( idStr );
        VertexShader* v = new VertexShader;
        FragmentShader* f = new FragmentShader;
        ShaderProgram* shader = new ShaderProgram;
        shader->SetVS( v );
        shader->SetFS( f );
        FileStream stream;
        stream.Open( "resources/" + vertex );
        v->Load( stream.ReadAll().c_str() );
        stream.Close();
        stream.Open( "resources/" + fragment );
        f->Load( stream.ReadAll().c_str() );
        stream.Close();

        shader->Link();
        shader->SetCameraUse( camera );

        shaders.insert( std::pair< wash, ShaderProgram* >( id, shader ) );
    }

    Texture* GetTexture( const std::string& name ) {
        wash id = Wash::Get( name );
        return textures[id];
    }

    ShaderProgram* GetShader( const std::string& name ) {
        wash id = Wash::Get( name );
        return shaders[id];
    }

    void UnloadAll() {
        for( auto it = textures.begin(); it != textures.end(); it++ ) {
            it->second->Destroy();
        }
    }

}
