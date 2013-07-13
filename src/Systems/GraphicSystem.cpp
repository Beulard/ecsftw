#include "GraphicSystem.hpp"
#include "ComponentManager.hpp"
#include "ResourceManager.hpp"
#include "vec2.hpp"
#include "Texture.hpp"
#include "EntityManager.hpp"
#include "SpriteFactory.hpp"

namespace GraphicSystem {

	std::map< u32, Component* > entities;
	std::map< wash, SpriteBatch* > batches;

	void Attach( u32 id ) {
		GraphicComponent* spriteComponent = ComponentManager::Create<GraphicComponent>();
		spriteComponent->batchID = -1;
		entities.insert( std::pair< u32, Component* >( id, spriteComponent ) );
	}

	void Detach( u32 id ) {
		auto it = entities.find( id );
		if( it == entities.end() ) {
			Error( "Entity %d has no graphic component attached !", id );
			return;
		}
		ComponentManager::Destroy<GraphicComponent>( it->second );
		entities.erase( it );
	}

	bool IsAttached( u32 id ) {
		if( entities.find( id ) != entities.end() )
			return true;
		return false;
	}

	/*
	void GraphicSystem::AttachText( u32 id ) {
		texts.insert( std::pair< u32, std::vector<u32> >( id, std::vector<u32>() ) );
		Attach( id );
	}

	void GraphicSystem::DetachText( u32 id ) {
		auto it = texts.find( id );
		if( it == texts.end() ) {
			Error( "Entity %d has no text !", id );
			return;
		}
		std::vector<u32>& ents = it->second;
		for( u32 i = 0; i < ents.size(); ++i ) {
			Detach( ents[i] );
		}
		texts.erase( it );
		Detach( id );
	}

	void GraphicSystem::AttachAnim( u32 id ) {
		anims.insert( std::pair< u32, std::vector<u32> >( id, std::vector<u32>() ) );
		Attach( id );
	}

	void GraphicSystem::DetachAnim( u32 id ) {
		auto it = anims.find( id );
		if( it == anims.end() ) {
			Error( "Entity %d has no text !", id );
			return;
		}
		std::vector<u32>& ents = it->second;
		for( u32 i = 0; i < ents.size(); ++i ) {
			Detach( ents[i] );
		}
		anims.erase( it );
		Detach( id );
	}*/

	void AddSpriteBatch( const std::string& name, SpriteBatch* batch ) {
		wash id = Wash::Get( name );
		batches.insert( std::pair< wash, SpriteBatch* >( id, batch ) );
	}

	void SetSpriteBatch( u32 id, const std::string& batch ) {
		wash batchID = Wash::Get( batch );
		auto it = batches.find( batchID );
		if( it == batches.end() ) {
			Error( "Could not find sprite batch %s", batch.c_str() );
			return;
		}
		((GraphicComponent*)entities[id])->batch = it->second;
	}

	void SetSpriteBatch( u32 id, SpriteBatch* batch ) {
		((GraphicComponent*)entities[id])->batch = batch;
	}

	void SetSpritePosition( u32 id, int x, int y ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		sprite->x = x;
		sprite->y = y;
	}

	void SetSpriteSize( u32 id, int w, int h ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		sprite->width = w;
		sprite->height = h;
	}

	void SetSpriteTexCoords( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		vec2ui sz = sprite->batch->GetTexture()->GetSize();
		sprite->topLeftX = (float)topLeftX / sz.x;
		sprite->topLeftY = (float)topLeftY / sz.y;
		if( bottomRightX == 0 && bottomRightY == 0 ) {
			sprite->bottomRightX = 1.f;
			sprite->bottomRightY = 1.f;
		}
		else {
			sprite->bottomRightX = (float)bottomRightX / sz.x;
			sprite->bottomRightY = (float)bottomRightY / sz.y;
		}
	}
	/*
	void GraphicSystem::SetTextString( u32 id, const std::string& s ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		auto it = texts.find( id );
		if( it != texts.end() ) {
			for( u32 i = 0; i < it->second.size(); ++i ) {
				Detach( it->second[i] );
			}
		}
		else
			it = texts.insert( std::pair< u32, std::vector<u32> >( id, std::vector<u32>() ) ).first;
		std::vector<u32>& ents = it->second;
		ents.resize( s.size());
		u32 currentPos = 0;
		for( u32 i = 0; i < s.size(); ++i ) {
			ents[i] = EntityManager::Create();
			u32 coord = ids[s[i]] * 14;
			Attach( ents[i] );
			SetSpriteBatch( ents[i], sprite->batch );
			SetSpriteSize( ents[i], 14, 13 );
			if( s[i] == ' ' )
				SetSpriteTexCoords( ents[i], 0, 0, 1, 1 );
			else
				SetSpriteTexCoords( ents[i], coord, 0, coord + 14, 13 );
			SetSpritePosition( ents[i], currentPos, 0 );
			if( s[i] == ' ' )
				currentPos += 7;
			else
				currentPos += advanceList[ids[s[i]]];
		}
	}

	void GraphicSystem::SetTextPosition( u32 id, int x, int y ) {
		std::vector<u32>& ents = texts[id];
		u32 xOffsets[ents.size()];
		if( ents.size() > 1 ) {
			for( u32 i = 1; i < ents.size(); ++i ) {
				GraphicComponent* compo0 = (GraphicComponent*)entities[ents[i - 1]];
				GraphicComponent* compo1 = (GraphicComponent*)entities[ents[i]];
				xOffsets[i - 1] = compo1->x - compo0->x;
			}
		}
		u32 currentOffset = 0;
		for( u32 i = 0; i < ents.size(); ++i ) {
			if( i == 0 )
				SetSpritePosition( ents[i], x , y );
			else
				SetSpritePosition( ents[i], x + currentOffset, y );
			currentOffset += xOffsets[i];
		}
	}

	void GraphicSystem::SetAnimPosition( u32 id, int x, int y ) {
		std::vector<u32>& ents = anims[id];
		for( u32 i = 0 ; i < ents.size(); ++i ) {
			SetSpritePosition( ents[i], x, y );
		}
	}

	void GraphicSystem::SetAnimSize( u32 id, int w, int h ) {
		std::vector<u32>& ents = anims[id];
		for( u32 i = 0 ; i < ents.size(); ++i ) {
			SetSpriteSize( ents[i], w, h );
		}
	}

	void GraphicSystem::AddFrame( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, float time ) {
		GraphicComponent* anim = (GraphicComponent*)entities[id];
		std::vector<u32>& ents = anims[id];
		ents.push_back( EntityManager::Create() );
		Attach( ents.back() );
		GraphicComponent* newFrame = (GraphicComponent*)entities[ents.back()];
		SetSpriteBatch( ents.back(), anim->batch );
		SetSpritePosition( ents.back(), anim->x, anim->y );
		SetSpriteTexCoords( ents.back(), topLeftX, topLeftY, bottomRightX, bottomRightY );
		SetSpriteSize( ents.back(), anim->width, anim->height );
		newFrame->time = time;
	}*/

	void Draw( u32 id ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		sprite->batch->Add( sprite );
	}

	void StopDrawing( u32 id ) {
		GraphicComponent* sprite = (GraphicComponent*)entities[id];
		sprite->batch->Remove( sprite );
	}

	bool IsDrawn( u32 id ) {
		return (((GraphicComponent*)entities[id])->batchID != -1);
	}
	/*
	void GraphicSystem::DrawText( u32 id ) {
		std::vector<u32>& ents = texts[id];
		for( u32 i = 0; i < ents.size(); ++i ) {
			Draw( ents[i] );
		}
	}

	void GraphicSystem::StopDrawingText( u32 id ) {
		std::vector<u32>& ents = texts[id];
		for( u32 i = 0; i < ents.size(); ++i ) {
			StopDrawing( ents[i] );
		}
	}

	bool GraphicSystem::IsTextDrawn( u32 id ) {
		std::vector<u32>& ents = texts[id];
		return IsDrawn( ents.back() );
	}

	void GraphicSystem::DrawAnim( u32 id ) {
		std::vector<u32>& ents = anims[id];
		for( u32 i = 0; i < ents.size(); ++i ) {
			Draw( ents[i] );
		}
	}

	void GraphicSystem::StopDrawingAnim( u32 id ) {
		std::vector<u32>& ents = anims[id];
		for( u32 i = 0; i < ents.size(); ++i ) {
			StopDrawing( ents[i] );
		}

	}

	bool GraphicSystem::IsAnimDrawn( u32 id ) {
		std::vector<u32>& ents = anims[id];
		return IsDrawn( ents.back() );
	}*/

	void Render() {
		for( auto it = batches.begin(); it != batches.end(); it++ )
			it->second->Render();
	}

}

