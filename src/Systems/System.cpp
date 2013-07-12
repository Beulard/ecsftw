#include "System.hpp"

System::System() {

}

System::~System() {

}

bool System::IsAttachedTo( u32 id ) {
    auto it = entities.find( id );
    if( it == entities.end() )
        return false;
    return true;
}
