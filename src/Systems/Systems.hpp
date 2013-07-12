#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP
#include <map>
#include "Wash.hpp"

class System;
namespace Systems {

    void Add( const std::string& name, System* s );
    System* Get( const std::string& name );
    std::map< wash, System* >& GetAll();

    void Destroy();

}

#endif // SYSTEMS_HPP
