#include "SpriteFactory.hpp"
#include "GraphicSystem.hpp"
#include "Systems.hpp"

namespace SpriteFactory {

    void AttachSprite( u32 id, const std::string& batch, const Pos& pos, const Size& size, const TexCoord& topLeft = TexCoord(0, 0), const TexCoord& bottomRight = TexCoord(0, 0) ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        graphic->Attach( id );
        graphic->SetSpriteBatch( id, batch );
        graphic->SetSpritePosition( id, pos.x, pos.y );
        graphic->SetSpriteSize( id, size.x, size.y );
        graphic->SetSpriteTexCoords( id, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y );
    }

    void DetachSprite( u32 id ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        graphic->Detach( id );
    }

}
