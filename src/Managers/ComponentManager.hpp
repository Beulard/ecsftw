#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP
#include <map>
#include <list>
#include <vector>
#include <memory.h>
#include <typeindex>
#include <typeinfo>
#include "Common.hpp"
#include "Component.hpp"

typedef std::type_index type_index;
typedef unsigned int u32;

template< class T > type_index GetTypeIndex() { return type_index(typeid(T)); }

namespace ComponentManager {

    //  This lets us have a contiguous buffer for each component type
    extern std::map< type_index, Component* > buffers;
    //  With this map we can retrieve one Component's index in its buffer
    extern std::map< Component*, u32 > indexes;
    //  In these vectors we will keep track of the free memory spots inside our buffers
    extern std::map< type_index, std::vector< bool > > used;

    //  Registers a new component type to the factory and allocates a buffer for it
    //  You can specify a component count for every type (default = 20)
    template< class T >
    void AddComponentType( u32 count = 20 ) {
       type_index id = GetTypeIndex<T>();
       T* buffer = new T[count];
       buffers.insert( std::pair< type_index, Component* > ( id, (Component*)buffer ) );
       auto it = used.insert( std::pair< type_index, std::vector<bool> >( id, std::vector<bool>() ) );
       for( u32 i = 0; i < count; ++i )
           it.first->second.push_back( false );
    }

    //  Free every buffer's allocated memory
    void Free();

    //  Create a new component of type T on the corresponding buffer and returns it
    template< class T >
    T* Create() {
       type_index id = GetTypeIndex<T>();
       auto it = buffers.find(id);
       if( it != buffers.end() ) {
           Component* buffer = it->second;
           std::vector<bool>& vec = used.find(id)->second;
           u32 firstAvailable = 0;
           for( u32 i = 0; i < vec.size(); ++i ) {
               if( vec[i] == false ) {
                   firstAvailable = i;
                   vec[i] = true;
                   break;
               }
               else if( i == vec.size() - 1 ) {
                   Error( "Trying to create too much %s !", id.name() );
                   return NULL;
               }
           }
           u32 offset = firstAvailable * sizeof(T);
           T* c = new(buffer + offset) T;
           //   Let's zero the component's data out by default : the system/factory will set the values manually
           memset( c, 0, sizeof(T) );
           indexes.insert( std::pair< Component*, u32 >( (Component*)c, firstAvailable ) );
           return c;
       }
       else {
           Error( "Component type not registered..." );
           return NULL;
       }
    }

    template< class T >
    void Destroy( Component* c ) {
        auto it = indexes.find( c );
        if( it == indexes.end() ) {
            Error( "Trying to destroy nonexistent component" );
            return;
        }
        memset( c, 0, sizeof(T) );
        u32 id = it->second;
        used.find(GetTypeIndex<T>())->second[id] = false;
    }

}

#endif // COMPONENTMANAGER_HPP
