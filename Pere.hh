#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hh"
#include "Personnage.hh"
#include "Objet.hh"

class Pere : public Personnage{
    public:

        Pere():Personnage(":/pere.png",":/pere_tete.png",true,100,120,false,100,4,"JP"){this->setBunker(true);};
        ~Pere(){};

        std::vector<Objet*> partir(bool * retour, std::vector<Objet*> objet);
        void besoins_vitaux(int folie);
        void soigner();

    //private:

};
