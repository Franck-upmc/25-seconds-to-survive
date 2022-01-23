#include "Entity.hh"
#include "Personnage.hh"
#include "Pere.hh"
#include "Objet.hh"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

// méthode qui permet au pere de partir en expedition et de ramener ou non des objets
std::vector<Objet*> Pere::partir(bool * retour, std::vector<Objet*> objet){

    if(objet[0]->getType()==AUTRE){
        objet[0]->setQuantite(0);
    }
    else{
        objet[0]->setQuantite(1);
    }

    std::srand(time(nullptr));
    int proba=rand() % 100;
    std::cout << "proba : " << proba << std::endl;
    setBunker(false);
    Type main_objet;

    // on récupere le type de l'objet avec lequel le pere est parti
    main_objet=objet[0]->getType();

    // si le pere part sans masque à gaz, alors il revient malade
    if(main_objet!=MASQUE_GAZ){
        _maladie=true;
        setImages(":/pere_malade.png",":/pere_malade_tete.png");
    }

    // suivant le type d'objet avec lequelle il part, le fils revient avec des objets differents
    switch(main_objet){

        case AUTRE :{
            if (proba > 50){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }
            else{
                Objet *eau= new Objet("EAU",1,EAU);
                objet.push_back(eau);
            }
            break;
        }

        case RADIO :{
            if (proba > 80){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 10){
                    objet[0]->setQuantite(0);
                }
                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",1,EAU);
                Objet *fusil= new Objet("FUSIL",1,FUSIL);

                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(fusil);
                _sante_mentale+=15;
            }
        break;
        }

        case LAMPE_TORCHE :{

            if (proba > 82){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 15){
                    objet[0]->setQuantite(0);
                }

                Objet *eau= new Objet("EAU",3,EAU);
                Objet *livre= new Objet("LIVRE",1,LIVRE);


                objet.push_back(eau);
                objet.push_back(livre);
            }
            break;
        }

        case CORDE :{

            if (proba > 85){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 10){
                    objet[0]->setQuantite(0);
                }
                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *jeu= new Objet("JEUX_SOCIETE",1,JEUX_SOCIETE);

                objet.push_back(nourriture);
                objet.push_back(jeu);
            }

            break;
        }


        case FUSIL :{
            if (proba > 90){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 30){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);
                Objet *soin= new Objet("EAU",1,KIT_SOIN);

                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(soin);
            }
        break;
        }

        case HACHE :{
            if (proba > 88){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 25){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);
                Objet *masque= new Objet("MASQUE_GAZ",1,MASQUE_GAZ);


                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(masque);
            }

        break;
        }

        case MASQUE_GAZ :{
            if (proba > 77){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 30){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);
                Objet *soin= new Objet("EAU",1,KIT_SOIN);

                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(soin);
            }
        break;
        }

        default:{
            break;
        }

    }

    
    return objet;
}

// le pere perd de la faim, de la soif et de la santé mentale tous les jours.
void Pere::besoins_vitaux(int folie){
    _faim-=14;
    _soif-=20;
    _sante_mentale-=folie;

    if(_faim <= 0 ){
        _cause_mort = _nom + " est mort de faim !!!";
        _vie = false;
    }
    else if(_soif <=0 ){
        _cause_mort = _nom + " est mort de soif !!!";
        _vie = false;
    }

    else if(_sante_mentale<=0){
        _cause_mort = _nom + " s'est sucidé car il était devenu fou !!!";
        _vie = false;
    }

}

// méthode qui permet de soigner le pere et qui change donc l'affichage du personnage
void Pere::soigner(){
    _maladie=false;
    setImages(":/pere.png",":/pere_tete.png");
}
