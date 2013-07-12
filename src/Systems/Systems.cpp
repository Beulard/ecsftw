#include "Systems.hpp"
#include "System.hpp"
#include "Common.hpp"

namespace Systems {

    std::map< wash, System* > systems;

    void Add( const std::string& name, System* s ) {
        wash id = Wash::Get( name );
        systems.insert( std::pair< wash, System* >( id, s ) );
    }

    System* Get( const std::string& name ) {
        wash id = Wash::Get( name );
        return systems[id];
    }

    std::map< wash, System* >& GetAll() {
        return systems;
    }

    void Destroy() {
        for( auto it = systems.begin(); it != systems.end(); it++ )
            delete it->second;
    }

}
