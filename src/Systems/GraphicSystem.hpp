#ifndef SPRITESYSTEM_HPP
#define SPRITESYSTEM_HPP
#include "SpriteBatch.hpp"
#include "Wash.hpp"

namespace GraphicSystem {

	void Attach( u32 id );
	void Detach( u32 id );
	bool IsAttached( u32 id );

	void AddSpriteBatch( const std::string& name, SpriteBatch* batch );

	void SetSpriteBatch( u32 id, const std::string& name );
	void SetSpriteBatch( u32 id, SpriteBatch* batch );
	void SetSpritePosition( u32 id, int x, int y );
	void SetSpriteSize( u32 id, int w, int h );
	void SetSpriteTexCoords( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY );

	void Draw( u32 id );
	void StopDrawing( u32 id );
	bool IsDrawn( u32 id );

	void Render();

}

#endif // SPRITESYSTEM_HPP
