#include "SpriteBatch.hpp"
#include "Component.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Common.hpp"
#include "Camera.hpp"

SpriteBatch::SpriteBatch() {
    glGenBuffers( 1, &vbID );
    glGenBuffers( 1, &uvID );
    Info( "%d %d", vbID, uvID );
}

SpriteBatch::SpriteBatch( Texture* tex, ShaderProgram* s ) : texture(tex), shader(s) {
    glGenBuffers( 1, &vbID );
    glGenBuffers( 1, &uvID );
}

SpriteBatch::~SpriteBatch() {
    glDeleteBuffers( 1, &vbID );
    glDeleteBuffers( 1, &uvID );
}

void SpriteBatch::Add( GraphicComponent* sprite ) {
    u32 id = sprites.size();
    sprites.push_back( sprite );
    sprite->batchID = id;
    vertices.push_back( vertexset() );
    uvs.push_back( uvset() );
    Update( sprite );
}

void SpriteBatch::Update( GraphicComponent* sprite ) {
    u32 id = sprite->batchID;
    vertices[id] = vertexset{ sprite->x, sprite->y,
            sprite->x + sprite->width, sprite->y,
            sprite->x + sprite->width, sprite->y + sprite->height,
            sprite->x, sprite->y + sprite->height };
    uvs[id] = uvset{ sprite->topLeftX, sprite->topLeftY,
                     sprite->bottomRightX, sprite->topLeftY,
                     sprite->bottomRightX, sprite->bottomRightY,
                     sprite->topLeftX, sprite->bottomRightY };
    needsUpdate = true;
}

void SpriteBatch::Remove( GraphicComponent* sprite ) {
    u32 id = sprite->batchID;
    sprite->batchID = -1;

    if( id != sprites.size() - 1 ) {
        sprites[id] = sprites.back();
        sprites[id]->batchID = id;
    }
    memcpy( &vertices[id], &vertices.back(), sizeof( vertexset ) );
    memcpy( &uvs[id], &uvs.back(), sizeof( uvset ) );
    sprites.pop_back();
    vertices.pop_back();
    uvs.pop_back();
}

void SpriteBatch::Update() {
    glBindBuffer( GL_ARRAY_BUFFER, vbID );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( vertexset ), &vertices[0], GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, uvID );
    glBufferData( GL_ARRAY_BUFFER, uvs.size() * sizeof(uvset), &uvs[0], GL_DYNAMIC_DRAW );
    needsUpdate = false;
}

void SpriteBatch::Render() {
    if( needsUpdate )
        Update();

    shader->Use();
    texture->Bind();

    int index = shader->GetUniformLocation( "projMat" );
    if( index == -1 ) {
        Error( "No uniform 'projMat' in shader" );
        return;
    }
    glUniformMatrix3fv( index, 1, GL_FALSE, projMatrix );

    if( shader->UsesCamera() ) {
        index = shader->GetUniformLocation( "camPos" );
        if( index == -1 )
            Error( "No uniform 'camPos' in shader" );
        glUniform2f( index, Camera::GetPosition().x, Camera::GetPosition().y );
    }

    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, vbID );
    glVertexAttribPointer( 0, 2, GL_INT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray(1);
    glBindBuffer( GL_ARRAY_BUFFER, uvID );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays( GL_QUADS, 0, vertices.size() * 4 );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

Texture* SpriteBatch::GetTexture() {
    return texture;
}
