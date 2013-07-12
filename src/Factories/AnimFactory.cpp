#include "AnimFactory.hpp"
#include "GraphicSystem.hpp"
#include "Systems.hpp"

namespace AnimFactory {

    void AttachAnim( u32 id, const std::string& batch, const Pos& pos, const Size& sz, const std::vector<FrameInfo>& frames ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        graphic->AttachAnim( id );
        graphic->SetSpriteBatch( id, batch );
        for( u32 i = 0; i < frames.size(); ++i ) {
            graphic->AddFrame( id, frames[i].topLeft.x, frames[i].topLeft.y, frames[i].bottomRight.x, frames[i].bottomRight.y, frames[i].time );
        }
        graphic->SetAnimPosition( id, pos.x, pos.y );
        graphic->SetAnimSize( id, sz.x, sz.y );
    }

    void DetachAnim( u32 id ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        graphic->DetachAnim( id );
    }

}
