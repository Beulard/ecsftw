#include "AnimManager.hpp"
#include "SpriteFactory.hpp"
#include "EntityManager.hpp"
#include "GraphicSystem.hpp"
#include "Time.hpp"
#include <map>
#include <vector>
#include <set>

struct Frame {
	Frame() {}
	Frame( u32 i, float f ) : id(i), time(f) {}
	u32 id;
	float time;
};

struct Anim {
	Anim() {}
	Anim( const std::string& b, int pX, int pY, int pW, int pH ) : batch(b), x(pX), y(pY), w(pW), h(pH), currentFrame(0), currentTime(0.f) {}

	std::string batch;
	int x, y;
	u32 w, h;
	u32 currentFrame;
	float currentTime;
	std::vector< Frame > frames;
};

namespace AnimManager {

	//  Stores all the stuff an anim uses
	std::map< u32, Anim > anims;
	//  Animations that will be updated and drawn
	std::set< u32 > active;

	void Create( u32 id, const std::string& batch, int x, int y, int w, int h ) {
		anims.insert( std::pair< u32, Anim >( id, Anim(batch, x, y, w, h) ) );
	}

	void Destroy( u32 id ) {
		std::vector<Frame>& frames = anims[id].frames;
		for( u32 i = 0; i < frames.size(); ++i ) {
			SpriteFactory::DetachSprite( frames[i].id );
			EntityManager::Destroy( frames[i].id );
		}
		anims.erase( anims.find( id ) );
	}

	void AddFrame( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, float time ) {
		Anim& anim = anims[id];
		anim.frames.push_back( Frame( EntityManager::Create(), time ) );
		SpriteFactory::AttachSprite( anim.frames.back().id, anim.batch, Pos( anim.x, anim.y ), Size( anim.w, anim.h ), TexCoord( topLeftX, topLeftY ), TexCoord( bottomRightX, bottomRightY ) );
	}

	void Draw( u32 id ) {
		const Anim& anim = anims[id];
		active.insert( id );
		GraphicSystem::Draw( anim.frames[anim.currentFrame].id );
	}

	void StopDrawing( u32 id ) {
		const Anim& anim = anims[id];
		GraphicSystem::StopDrawing( anim.frames[anim.currentFrame].id );
		active.erase( active.find( id ) );
	}

	bool IsDrawn( u32 id ) {
		if( GraphicSystem::IsDrawn( anims[id].frames[anims[id].currentFrame].id ) )
			return true;
		return false;
	}

	void Update() {
		float elapsed = Time::GetElapsed();
		for( auto it = active.begin(); it != active.end(); ++it ) {
			Anim& anim = anims[*it];
			anim.currentTime += elapsed;
			if( anim.currentTime >= anim.frames[anim.currentFrame].time ) {
				GraphicSystem::StopDrawing( anim.frames[anim.currentFrame].id );
				anim.currentFrame++;
				if( anim.currentFrame >= anim.frames.size() )
					anim.currentFrame = 0;
				GraphicSystem::Draw( anim.frames[anim.currentFrame].id );
				anim.currentTime = 0.f;
			}
		}
	}

}
