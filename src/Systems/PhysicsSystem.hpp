#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

typedef unsigned int u32;

namespace PhysicsSystem {

	void Attach( u32 id );
	void Detach( u32 id );
	bool IsAttached( u32 id );

}

#endif // PHYSICSSYSTEM_HPP
