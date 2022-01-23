#include "Entity.hh"
#include <iostream>


Entity::Entity(std::string image){
	_image=image;
}



Entity::Entity(const Entity &e){
	_image=e._image;

}