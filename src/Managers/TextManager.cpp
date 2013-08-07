#include "TextManager.hpp"
#include <map>
#include <vector>
#include "EntityManager.hpp"
#include "SpriteFactory.hpp"
#include "GraphicSystem.hpp"

char charList[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

char advanceList[] = {
	/*a*/7, 7, 7, 7, 6, /*f*/5, 7, 7, 3, /*j*/5, 7, 4, 11, 7, 7, /*p*/7, 7, 5, 5, 5, 7, 7, /*w*/9, 7, 7, 7,
	/*A*/8, 8, 9, 9, 7, 6, 8, 8, /*I*/5, 7, 8, 7, 9, 8, 8, /*P*/7, 8, 7, 7, 8, 8, 8, /*W*/10, 7, 8, 7,
	/*0*/7, 7, 7, 7, 8, 8, 7, 7, 7, 7
};

struct Text {
		Text() {}
		Text( const std::string& b, int pX, int pY ) : batch(b), x(pX), y(pY) {}
	std::string batch;
	int x, y;
	std::vector<u32> chars;
};


namespace TextManager {

	std::map< u32, Text > texts;
	std::map< char, u32 > ids;

	void Init() {
		for( u32 i = 0; i < 62; ++i )
			ids.insert( std::pair< char, u32 >( charList[i], i ) );
	}

	void Create( u32 id, const std::string& batch, int x, int y, const std::string& text ) {
		texts.insert( std::pair< u32, Text >( id, Text( batch, x, y ) ) );
		SetString( id, text );
	}

	void Destroy( u32 id ) {
		std::vector<u32>& chars = texts[id].chars;
		for( u32 i = 0; i < chars.size(); ++i ) {
			SpriteFactory::DetachSprite( chars[i] );
			EntityManager::Destroy( chars[i] );
		}
	}

	void SetString( u32 id, const std::string& s ) {
		Text& text = texts[id];
		std::vector<u32>& chars = text.chars;
		u32 currentX = text.x;
		for( u32 i = 0; i < s.size(); ++i ) {
			chars.push_back( EntityManager::Create() );
			TexCoord topLeft( 14 * ids[s[i]], 0 );
			TexCoord bottomRight( topLeft.x + 14, 13 );
			if( s[i] == ' ' ) {
				topLeft.x = 0;
				topLeft.y = 0;
				bottomRight.x = 1;
				bottomRight.y = 1;
			}

			SpriteFactory::AttachSprite( chars.back(), text.batch, Pos(currentX, text.y), Size(14, 13), topLeft, bottomRight );
			if( s[i] == ' ' )
				currentX += 8;
			else
				currentX += advanceList[ids[s[i]]];
		}
	}

	void Draw( u32 id ) {
		std::vector<u32>& chars = texts[id].chars;
		for( u32 i = 0; i < chars.size(); ++i ) {
			GraphicSystem::Draw( chars[i] );
		}
	}

	void StopDrawing( u32 id ) {
		std::vector<u32>& chars = texts[id].chars;
		for( u32 i = 0; i < chars.size(); ++i ) {
			GraphicSystem::StopDrawing( chars[i] );
		}
	}

	bool IsDrawn( u32 id ) {
		if( GraphicSystem::IsDrawn( texts[id].chars.back() ) )
			return true;
		return false;
	}

}
