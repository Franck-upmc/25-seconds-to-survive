#include "Entity.hh"
#include "Personnage.hh"
#include "Mere.hh"
#include "Objet.hh"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

// méthode qui permet à la mère de partir en expedition et de ramener ou non des objets
std::vector<Objet*> Mere::partir(bool * retour, std::vector<Objet*> objet){

    if(objet[0]->getType()==AUTRE){
        objet[0]->setQuantite(0);
    }
    else{
        objet[0]->setQuantite(1);
    }


    std::srand(time(nullptr));
    int proba=rand() % 100;
    setBunker(false);
    Type main_objet;
    main_objet=objet[0]->getType();

    // si la mère part sans masque à gaz, alors elle revient malade
    if(main_objet!=MASQUE_GAZ){
        _maladie=true;
        setImages(":/mere_malade.png",":/mere_tete_malade.png");
    }

    // suivant le type d'objet avec lequelle elle part, la mère revient avec des objets differents
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

                Objet *eau= new Objet("EAU",1,EAU);
                objet.push_back(eau);

                _sante_mentale+=10;
            }
        break;
        }

        case LAMPE_TORCHE :{

            if (proba > 87){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 15){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *corde= new Objet("CORDE",1,CORDE);


                objet.push_back(nourriture);
                objet.push_back(corde);
            }
            break;
        }

        case CORDE :{

            if (proba > 90){
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
                objet.push_back(nourriture);
            }

            break;
        }


        case FUSIL :{
            if (proba > 95){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 30){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",1,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);
                Objet *masque= new Objet("MASQUE_GAZ",1,MASQUE_GAZ);

                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(masque);
            }
        break;
        }

        case HACHE :{
            if (proba > 93){
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
                Objet *eau= new Objet("EAU",1,EAU);
                Objet *soin= new Objet("KIT_SOIN",1,KIT_SOIN);


                objet.push_back(nourriture);
                objet.push_back(eau);
                objet.push_back(soin);
            }

        break;
        }
        case MASQUE_GAZ :{
            if (proba > 75){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 30){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",1,NOURRITURE);
                Objet *soin= new Objet("EAU",1,KIT_SOIN);

                objet.push_back(nourriture);
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


// la mere perd de la faim, de la soif et de la santé mentale tous les jours.
void Mere::besoins_vitaux(int folie){
    _faim-=11;
    _soif-=15;
    _sante_mentale-=folie;

    // si un des attributs est plus petit que 0, alors le personnage meurt
    if(_faim <= 0 ){
        _cause_mort = _nom + " est morte de faim !!!";
        _vie = false;
    }
    else if(_soif <=0 ){
        _cause_mort = _nom + " est morte de soif !!!";
        _vie = false;
    }

    else if(_sante_mentale<=0){
        _cause_mort = _nom + " s'est sucidée car elle était devenu folle !!!";
        _vie = false;
    }

}


// méthode qui permet de soigner la mère et qui change donc l'affichage du personnage
void Mere::soigner(){

    _maladie=false;
    setImages(":/mere.png",":/mere_tete.png");
}
