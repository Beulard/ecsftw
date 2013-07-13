#ifndef ANIMMANAGER_HPP
#define ANIMMANAGER_HPP
#include <string>

typedef unsigned int u32;
class SpriteBatch;

namespace AnimManager {

	void Create( u32 id, const std::string& batch, int x, int y, int w, int h );
	void Destroy( u32 id );

	void AddFrame( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, float time );

	void Draw( u32 id );
	void StopDrawing( u32 id );
	bool IsDrawn( u32 id );

	void Update();

}

#endif // ANIMMANAGER_HPP
