#pragma once

#include "qglobal.h"
#include <list>
#include <iostream>
#include <string>
#include "Entity.hh"


typedef enum e_Type{
    NOURRITURE=0,
    EAU=1,
    KIT_SOIN=2,
    RADIO=3,
    MASQUE_GAZ=4,
    JEUX_SOCIETE=5,
    LAMPE_TORCHE=6,
    CORDE=7,
    LIVRE=8,
    FUSIL=9,
    HACHE=10,
    HORLOGE=11,
    CALENDRIER=12,
    PERE=13,
    MERE=14,
    FILS=15,
    FILLE=16,
    AUTRE=17
}Type;


class Objet : public Entity{
    public:
        Objet(std::string image,float quantite,Type type);
        Objet(float quantite,Type type);
        Objet(const Objet & o);

        //get
        float getQuantite(){return _quantite;};
        Type getType(){return _type;};

        // surcharge d'operateur
        Type operator()(){return _type;};
        Objet& operator+=(float value){_quantite+=value;return *this;};
        Objet& operator-=(float value){_quantite-=value;return *this;};

        //set
        void setQuantite(float quantite){_quantite=quantite;};
        void setType(Type type){_type=type;};
        void setImages(std::string imageCorps, std::string imageTete = std::string()) {_image = imageCorps;Q_UNUSED(imageTete)}
        


    private:
        float _quantite;
        Type _type;


};
