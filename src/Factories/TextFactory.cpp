#include "TextFactory.hpp"
#include "Wash.hpp"
#include "Texture.hpp"
#include "GraphicSystem.hpp"
#include "Systems.hpp"
#include <map>

typedef vec2i Pos;

namespace TextFactory {

    void AttachText( u32 id, const std::string& text, const std::string& batch, const Pos& pos ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        //graphic->AttachText( id );
        //graphic->SetSpriteBatch( id, batch );
        //graphic->SetTextString( id, text );
        //graphic->SetTextPosition( id, pos.x, pos.y );
    }

    void DetachText( u32 id ) {
        //GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        //graphic->DetachText( id );
    }

}
