#include "Entity.hh"
#include "Personnage.hh"
#include <iostream>


Personnage::Personnage(std::string image,std::string image_tete,bool vie,int faim,int soif,bool maladie,int sante_mentale,int expedition, std::string nom): Entity(image){
    _vie=vie;
    _faim=faim;
    _soif=soif;
    _faim_max=faim;
    _soif_max=soif;
    _maladie=maladie;
    _sante_mentale=sante_mentale;
    _expedition=expedition;
    _bunker=true;
    _nom=nom;
    _jour_malade=0;
    _image_tete=image_tete;
}


Personnage::Personnage(const Personnage & p) : Entity(p._image){
    _vie=p._vie;
    _faim=p._faim;
    _soif=p._soif;
    _maladie=p._maladie;
    _sante_mentale=p._sante_mentale;
    _expedition=p._expedition;
    _bunker=p._bunker;
    _nom=p._nom;
    _image_tete=p._image_tete;
}

void Personnage::manger(){
    _faim+=_faim_max/2;

    if(_faim>_faim_max){
        _faim=_faim_max;
    }
}

void Personnage::boire(){
    _soif+=_soif_max/2;

    if(_soif>_soif_max){
        _soif=_soif_max;
    }
}

void Personnage::affiche_info(){
    std::string s;
    s="\nNom :" + _nom + "\nVie : " + std::to_string(_vie) + "\nFaim : " + std::to_string(_faim) + "\nSoif : " +
    std::to_string(_soif) + "\nMaladie : " + std::to_string(_maladie) + "\nSante mentale : " +
    std::to_string(_sante_mentale) +"\nJour max expedition : " + std::to_string(_expedition) +
    "\nPresent dans le bunker : " + std::to_string(_bunker);

    std::cout << s << std::endl;
}
