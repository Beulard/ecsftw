#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP
#include <GL/glew.h>
#include "FileStream.hpp"

//  A set of vertices for 1 sprite
struct vertexset {
    int x1, y1,
        x2, y2,
        x3, y3,
        x4, y4;
};

//  A set of normalized texture coordinates for 1 sprite
struct uvset {
        float x1, y1,
              x2, y2,
              x3, y3,
              x4, y4;
};

class ShaderProgram;
struct GraphicComponent;
class SpriteBatch
{
    public:
        SpriteBatch();
        SpriteBatch( Texture* tex, ShaderProgram* s );
        ~SpriteBatch();

        void Add( GraphicComponent* sprite );
        void Update( GraphicComponent* sprite );
        void Remove( GraphicComponent* sprite );

        void Update();
        void Render();

        Texture* GetTexture();

        //  TODO find a solution to this problem :
        //  How do animations get handled in this CE system + batching ?

    private:
        Texture* texture;
        ShaderProgram* shader;
        std::vector< GraphicComponent* > sprites;
        //  Arrays of contiguous vertex and texture coordinate data for fast rendering
        std::vector< vertexset > vertices;
        std::vector< uvset > uvs;

        //  OpenGL IDs for our buffers
        GLuint vbID, uvID;

        bool needsUpdate;
};

#endif // SPRITEBATCH_HPP
