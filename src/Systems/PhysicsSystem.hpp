#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP
#include "System.hpp"

class PhysicsSystem : public System {
    public:
        PhysicsSystem();
        ~PhysicsSystem();

        virtual void Attach( u32 id );
        virtual void Detach( u32 id );

    private:
};

#endif // PHYSICSSYSTEM_HPP
