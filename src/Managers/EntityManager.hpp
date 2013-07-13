#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

typedef unsigned int u32;

namespace EntityManager {

    u32 Create();
    void Destroy( u32 id );
    void DestroyAll();

}

#endif // ENTITYMANAGER_HPP
