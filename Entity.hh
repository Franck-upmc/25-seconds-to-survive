#pragma once

#include <iostream>
#include <string>

class Entity{
    public:
        Entity(std::string image);
        Entity(){};
        Entity(const Entity &e);

        //getter
        std::string getImage(){return _image;};
        

        //setteur
        void setImage(std::string image){_image=image;};      
        
    protected:
        std::string _image;
        
    
};