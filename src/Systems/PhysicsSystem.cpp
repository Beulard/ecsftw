#include "PhysicsSystem.hpp"
#include "ComponentManager.hpp"

PhysicsSystem::PhysicsSystem() {

}

PhysicsSystem::~PhysicsSystem() {

}

void PhysicsSystem::Attach( u32 id ) {
    PhysicsComponent* physicsComponent = ComponentManager::Create<PhysicsComponent>();
    entities.insert( std::pair< u32, Component* >( id, physicsComponent ) );
}

void PhysicsSystem::Detach( u32 id ) {
    auto it = entities.find( id );
    if( it == entities.end() ) {
        Error( "Entity %d has no physics component attached !", id );
        return;
    }
    ComponentManager::Destroy<PhysicsComponent>( it->second );
    entities.erase( it );
}
