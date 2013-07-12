#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <map>

typedef unsigned int u32;

struct Component;
class System
{
    public:
        System();
        virtual ~System();

        //  Add the corresponding component to the entity
        virtual void Attach( u32 id ) = 0;
        //  Remove it
        virtual void Detach( u32 id ) = 0;

        //  Check if the entity has our component attached to it
        bool IsAttachedTo( u32 id );

    protected:
        std::map< u32, Component* > entities;
};

#endif // SYSTEM_HPP
