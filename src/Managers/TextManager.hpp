#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP
#include <string>

typedef unsigned int u32;

namespace TextManager {

	void Init();

	void Create( u32 id, const std::string& batch, int x, int y, const std::string& text );
	void Destroy( u32 id );

	void SetString( u32 id, const std::string& s );

	void Draw( u32 id );
	void StopDrawing( u32 id );
	bool IsDrawn( u32 id );

}

#endif // TEXTMANAGER_HPP
