#include "SpriteFactory.hpp"
#include "GraphicSystem.hpp"

namespace SpriteFactory {

	void AttachSprite( u32 id, const std::string& batch, const Pos& pos, const Size& size, const TexCoord& topLeft = TexCoord(0, 0), const TexCoord& bottomRight = TexCoord(0, 0) ) {
		GraphicSystem::Attach( id );
		GraphicSystem::SetSpriteBatch( id, batch );
		GraphicSystem::SetSpritePosition( id, pos.x, pos.y );
		GraphicSystem::SetSpriteSize( id, size.x, size.y );
		GraphicSystem::SetSpriteTexCoords( id, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y );
	}

	void DetachSprite( u32 id ) {
		GraphicSystem::Detach( id );
	}

}
