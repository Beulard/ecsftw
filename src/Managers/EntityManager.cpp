#include "EntityManager.hpp"
#include <vector>
#include "Systems.hpp"
#include "System.hpp"

namespace EntityManager {

    u32 nextID = 0;
    std::vector< u32 > availableIDs;
    u32 Create() {
        if( availableIDs.empty() )
            return nextID++;
        else {
            u32 id = availableIDs.back();
            availableIDs.pop_back();
            return id;
        }
    }

    void Destroy( u32 id ) {
        std::map< wash, System* >& systems = Systems::GetAll();
        for( auto it = systems.begin(); it != systems.end(); it++ ) {
            if( it->second->IsAttachedTo( id ) ) {
                it->second->Detach( id );
            }
        }
        availableIDs.push_back( id );
    }

    void DestroyAll() {
        //  While we didn't reach the 'nextID' value, we keep destroying
        //  Making sure the ID is not in the 'availbleIDs' vector
        for( u32 i = 0; i < nextID; ++i ) {
            bool destroy = true;
            for( u32 j = 0; j < availableIDs.size(); ++j ) {
                if( i == j )
                    destroy = false;
            }
            if( destroy )
                Destroy(i);
        }
    }

}
