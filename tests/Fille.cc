#include "Entity.hh"
#include "Personnage.hh"
#include "Fille.hh"
#include "Objet.hh"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

std::vector<Objet*> Fille::partir(bool * retour, std::vector<Objet*> objet){

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

    if(main_objet!=MASQUE_GAZ){
        _maladie=true;
        //setImageTete(":/fille_tete_malade.png");
        //setImage(":/fille_malade.png");
        setImages(":/fille_malade.png",":/fille_tete_malade.png");
    }

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
            if (proba > 75){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 20){
                    objet[0]->setQuantite(0);
                }

                Objet *eau= new Objet("EAU",3,EAU);
                Objet *fusil= new Objet("FUSIL",3,FUSIL);

                objet.push_back(eau);
                objet.push_back(fusil);


                _sante_mentale+=18;
            }
        break;
        }

        case LAMPE_TORCHE :{

            if (proba > 80){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 12){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",3,NOURRITURE);
                Objet *hache= new Objet("HACHE",1,HACHE);


                objet.push_back(nourriture);
                objet.push_back(hache);
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
                Objet *masque= new Objet("NOURRITURE",1,MASQUE_GAZ);

                objet.push_back(nourriture);
                objet.push_back(masque);

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
                if(proba <= 28){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);
                Objet *soin= new Objet("KIT_SOIN",1,KIT_SOIN);


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
                if(proba <= 20){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *soin= new Objet("KIT_SOIN",1,KIT_SOIN);


                objet.push_back(nourriture);
                objet.push_back(soin);
            }

        break;
        }

        default:{
            std::cout << "Not yet implemented" << std::endl;
            break;
        }



    }

    for(auto& i : objet){
        std::cout << "Type : " << i->getType() << " Qauntite : " << i->getQuantite() << std::endl;
    }
    return objet;
}

void Fille::besoins_vitaux(int folie){
    _faim-=8;
    _soif-=10;
    _sante_mentale-=folie;

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


void Fille::soigner(){
    _maladie=false;
    setImages(":/fille.png",":/fille_tete.png");
    //setImage(":/fille.png");
    //setImageTete(":/fille_tete.png");
}
