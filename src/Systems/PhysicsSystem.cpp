#include "PhysicsSystem.hpp"
#include "ComponentManager.hpp"

namespace PhysicsSystem {

	std::map< u32, Component* > entities;

	void Attach( u32 id ) {
		PhysicsComponent* physicsComponent = ComponentManager::Create<PhysicsComponent>();
		entities.insert( std::pair< u32, Component* >( id, physicsComponent ) );
	}

	void Detach( u32 id ) {
		auto it = entities.find( id );
		if( it == entities.end() ) {
			Error( "Entity %d has no physics component attached !", id );
			return;
		}
		ComponentManager::Destroy<PhysicsComponent>( it->second );
		entities.erase( it );
	}

	bool IsAttached( u32 id ) {
		if( entities.find( id ) != entities.end() )
			return true;
		return false;
	}

}
