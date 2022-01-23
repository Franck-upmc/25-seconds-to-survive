#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hh"
#include "Objet.hh"

class Personnage : public Entity{
    public:
        Personnage(std::string image,std::string image_tete,bool vie,int faim,int soif,bool maladie,int sante_mentale, int expedition, std::string nom);
        Personnage(const Personnage & p);
        virtual ~Personnage() = default;


        //setter
        void setFaim(int faim){_faim=faim;};
        void setSoif(int soif){_soif=soif;};
        void setMaladie(bool malade){_maladie=malade;};
        void setVie(bool vie){_vie=vie;};
        void setBunker(bool presence){_bunker=presence;};
        void setJourmalade(){_jour_malade++;};
        void setCausemort(std::string cause){_cause_mort=cause;};
        void setImageTete(std::string image_tete){_image_tete=image_tete;}
        void setImages(std::string imageCorps, std::string imageTete) {_image = imageCorps; _image_tete = imageTete;}



        //getter
        bool getVie(){return _vie;};
        std::string getNom(){return _nom;};
        int getSoif(){return _soif;};
        int getFaim(){return _faim;};
        int getSante_mentale(){return _sante_mentale;};
        bool getMaladie(){return _maladie;};
        int getExpedition(){return _expedition;};
        bool getBunker(){return _bunker;};
        int getJourmalade(){return _jour_malade;};
        std::string getCausemort(){return _cause_mort;};
        int getSoifmax(){return _soif_max;};
        int getFaimmax(){return _faim_max;};
        std::string getImageTete(){return _image_tete;}

        //fonction qui permet à un personnage de manger et de boire
        void manger();
        void boire();
        
        //affiche le personnage (debug)
        void affiche_info();

        //permet de soigner et de modifier l'apparence du personnage
        virtual void soigner()=0;

        //permet de partir en expedition
        virtual std::vector<Objet*> partir(bool * retour, std::vector<Objet*> objet)=0;

        //permet de diminuer les "points de vie" d'un personnage
        virtual void besoins_vitaux(int folie)=0;

    protected:
        bool _vie;
        int _faim;
        int _soif;
        int _faim_max;
        int _soif_max;
        bool _maladie;
        int _sante_mentale;
        int _expedition;
        bool _bunker;
        std::string _nom;
        int _jour_malade;
        std::string _cause_mort;
        std::string _image_tete;

};
