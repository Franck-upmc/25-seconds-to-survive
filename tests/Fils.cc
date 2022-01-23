#include "Entity.hh"
#include "Personnage.hh"
#include "Fils.hh"
#include "Objet.hh"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

std::vector<Objet*> Fils::partir(bool * retour, std::vector<Objet*> objet){

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
        //setImageTete(":/fils_malade_tete.png");
        //setImage(":/fils_malade.png");
        setImages(":/fils_malade.png",":/fils_malade_tete.png");
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
            if (proba > 78){
                *retour=false;
                for(auto &i : objet){
                    delete(i);
                }
            }

            else{
                if(proba <= 20){
                    objet[0]->setQuantite(0);
                }

                Objet *eau= new Objet("EAU",1,EAU);
                Objet *calendrier= new Objet("CALENDRIER",1,CALENDRIER);
                Objet *soin= new Objet("KIT_SOIN",1,KIT_SOIN);
                objet.push_back(eau);
                objet.push_back(calendrier);
                objet.push_back(soin);

                _sante_mentale+=20;
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
                if(proba <= 12){
                    objet[0]->setQuantite(0);
                }

                Objet *nourriture= new Objet("NOURRITURE",2,NOURRITURE);
                Objet *eau= new Objet("EAU",1,EAU);


                objet.push_back(nourriture);
                objet.push_back(eau);
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
                Objet *hache= new Objet("HACHE",1,HACHE);
                objet.push_back(nourriture);
                objet.push_back(hache);
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

                Objet *nourriture= new Objet("NOURRITURE",1,NOURRITURE);
                Objet *eau= new Objet("EAU",2,EAU);


                objet.push_back(nourriture);
                objet.push_back(eau);

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

void Fils::besoins_vitaux(int folie){
    _faim-=8;
    _soif-=10;
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

void Fils::soigner(){
    _maladie=false;
    setImages(":/fils.png",":/fils_tete.png");
    //setImage(":/fils.png");
    //setImageTete(":/fils_tete.png");
}
