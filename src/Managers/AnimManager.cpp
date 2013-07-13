#include "AnimManager.hpp"
#include "SpriteFactory.hpp"
#include "EntityManager.hpp"
#include "GraphicSystem.hpp"
#include "Systems.hpp"
#include "Time.hpp"
#include <map>
#include <vector>
#include <set>

struct Frame {
    u32 id;
    float time;
};

struct Anim {
    AnimInfo info;
    std::vector< Frame > frames;
};

namespace AnimManager {

    //  Stores all the stuff an anim uses
    std::map< u32, Anim > anims;
    //  Animations that will be updated and drawn
    std::set< u32 > active;

    void Create( u32 id, const AnimInfo& anim ) {
        anims.insert( std::pair< u32, Anim >( id, Anim{anim , std::vector<Frame>()} ) );
    }

    void Destroy( u32 id ) {
        std::vector<Frame>& frames = anims[id].frames;
        for( u32 i = 0; i < frames.size(); ++i ) {
            SpriteFactory::DetachSprite( frames[i].id );
            EntityManager::Destroy( frames[i].id );
        }
        anims.erase( anims.find( id ) );
    }

    void AddFrame( u32 id, const FrameInfo& frame ) {
        Anim& anim = anims[id];
        anim.frames.push_back( Frame{ EntityManager::Create(), frame.time } );
        SpriteFactory::AttachSprite( anim.frames.back().id, anim.info.batch, Pos( anim.info.x, anim.info.y ), Size( anim.info.w, anim.info.h ), TexCoord( frame.topLeftX, frame.topLeftY ), TexCoord( frame.bottomRightX, frame.bottomRightY ) );
    }

    void Draw( u32 id ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        const Anim& anim = anims[id];
        active.insert( id );
        graphic->Draw( anim.frames[anim.info.currentFrame].id );
    }

    void StopDrawing( u32 id ) {
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        const Anim& anim = anims[id];
        active.erase( active.find( id ) );
        graphic->StopDrawing( anim.frames[anim.info.currentFrame].id );
    }

    void Update() {
        float elapsed = Time::GetElapsed();
        GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
        for( auto it = active.begin(); it != active.end(); ++it ) {
            Anim& anim = anims[*it];
            anim.info.currentTime += elapsed;
            if( anim.info.currentTime >= anim.frames[anim.info.currentFrame].time ) {
                graphic->StopDrawing( anim.frames[anim.info.currentFrame].id );
                anim.info.currentFrame++;
                if( anim.info.currentFrame >= anim.frames.size() )
                    anim.info.currentFrame = 0;
                graphic->Draw( anim.frames[anim.info.currentFrame].id );
                anim.info.currentTime = 0.f;
            }
        }
    }

}
