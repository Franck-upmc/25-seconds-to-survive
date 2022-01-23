#include "Entity.hh"
#include "Objet.hh"
#include <iostream>


Objet::Objet(std::string image,float quantite,Type type): Entity(image){
    _quantite=quantite;
    _type=type;
}

Objet::Objet(float quantite,Type type): Entity(){
    _quantite=quantite;
    _type=type;
}


Objet::Objet(const Objet & o) : Entity(o._image){
    _quantite=o._quantite;
    _type=o._type;
}

