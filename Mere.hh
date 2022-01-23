#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hh"
#include "Personnage.hh"
#include "Objet.hh"

class Mere : public Personnage{
    public:
        Mere():Personnage(":/mere.png",":/mere_tete.png",true,80,80,false,100,3,"Irene"){this->setBunker(true);};
        ~Mere(){};

        std::vector<Objet*> partir(bool * retour, std::vector<Objet*> objet);
        void besoins_vitaux(int folie);
        void soigner();

    

};
