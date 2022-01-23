#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hh"
#include "Personnage.hh"
#include "Objet.hh"

class Fils: public Personnage{
    public:
        Fils(): Personnage(":/fils.png",":/fils_tete.png",true,60,60,false,70,2,"John"){this->setBunker(true);};
        ~Fils(){};

        std::vector<Objet*> partir(bool * retour, std::vector<Objet*> objet);
        void besoins_vitaux(int folie);
        void soigner();

    //private:

};
