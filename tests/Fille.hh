#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hh"
#include "Personnage.hh"
#include "Objet.hh"

class Fille: public Personnage{
    public:

        Fille(): Personnage(":/fille.png",":/fille_tete.png",true,60,60,false,60,2,"Laura"){this->setBunker(true);};
        ~Fille(){};

        std::vector<Objet*> partir(bool * retour, std::vector<Objet*> objet);
        void besoins_vitaux(int folie);
        void soigner();

    //private:

};
