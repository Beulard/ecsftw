#include "ComponentManager.hpp"

namespace ComponentManager {

    std::map< type_index, Component* > buffers;
    std::map< Component*, u32 > indexes;
    std::map< type_index, std::vector< bool > > used;

    void Free() {
        for( auto it = buffers.begin(); it != buffers.end(); it++ ) {
            delete[] it->second;
        }
    }

}
