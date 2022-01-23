#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "Entity.hh"
#include "Objet.hh"
#include "Personnage.hh"
#include "Pere.hh"
#include "Mere.hh"
#include "Fils.hh"
#include "Fille.hh"
#include "custompixmapitem.h"

typedef enum e_rationnement{
    rien =0,
    manger=1,
    boire=2,
    manger_boire=3,
    soin=4,
    manger_soin=5,
    boire_soin=6,
    manger_boire_soin=7
}Rationnement;

class Histoire{
    public:
        Histoire();
        ~Histoire();

        int getJour(){return _jour;};
        std::vector<Objet*> getListeObjet(){return _liste_objet;};
        std::vector<Objet*> getListeObjet_tot(){return _liste_objet_tot;};
        std::vector<Personnage*> getListePerso(){return _liste_perso;};

        // permet de récuperer le nombre de personnage en vie
        int enVie();

        // recupere la quantité totale d'eau, de nourriture et de kit de soin dans le bunker
        float getEau();
        float getNourriture();
        int getSoin();

        // permet de savoir si un personnage est déjà en expedition
        bool getExpedition();


        void setEau(float quantite);
        void setNourriture(float quantite);


        
        // permet de faire mourir un personnage
        void deces(Personnage* perso){perso->setVie(false);};

        // remplir la liste des objets du bunker avec l'inventaire fournit par l'affichage
        void setListeObjet(QList<CustomPixmapItem*> inventaire);
        
        // Initialise tous les objets du jeu dans _liste_obj_tot
        void init_Objet();

        //permet de passer au jour suivant
        void nv_jour(){_jour++;};

        //applique la méthode besoin_vitaux pour tous les personnages encore en vie
        void update_Perso();

        //permet de nourir/soigner les personnages en fonction de la selection du joueur
        void rationnement(std::vector<Rationnement> ratio);

        //permet d'envoyer un personnage en expedition avec un seul objet
        void expedition(Type perso, Type objet);

        //mise à jour de la liste d'objets du bunker avec ce que le personnage a ramené de son expedition
        void retour_expedition();
        void ajoutObjet_expe(Objet* objet){_objet_expe.push_back(objet);};


        //permet de supprimer un personnage de la liste si il est mort et de remplir un fichier .txt avec l'état des personnages
        void affiche_info();
        





    private:
        int _jour;
        int _depart_expe;
        std::vector<Objet*> _objet_expe;
        std::vector<Objet*> _liste_objet;
        std::vector<Personnage*> _liste_perso;
        std::vector<Objet*> _liste_objet_tot;
        std::string _tab_objet[13]{"boite de nourriture","bouteille d'eau","kit de soin", "radio","masque à gaz","jeu de societe","lampe torche",
        "corde","livre","fusil","hache","horloge","calendrier"};
        bool _reduction_stress;



};

