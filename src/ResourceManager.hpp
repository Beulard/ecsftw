#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <string>

class Texture;
class ShaderProgram;

namespace ResourceManager {

    void LoadTexture( const std::string& file );
    void LoadShader( const std::string& vertex, const std::string& fragment, bool camera );

    Texture* GetTexture( const std::string& name );
    ShaderProgram* GetShader( const std::string& name );

    void UnloadAll();

}

#endif // RESOURCEMANAGER_HPP
