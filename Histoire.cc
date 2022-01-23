#include "Histoire.hh"
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <random>
#include <algorithm>


Histoire::Histoire(){
    _jour=0;
    _depart_expe=0;
    _reduction_stress=false;
    init_Objet();
    std::ofstream file("historique.txt" );
    file.close();
    std::ofstream fichier("etat_perso.txt", std::ios::out | std::ios::trunc);
    fichier << "Jour : " << _jour << std::endl;
    fichier << "Les personnages sont arrivés dans le bunker juste à temps" << std::endl;
    fichier.close();


}

Histoire::~Histoire(){

    for(auto &i : _liste_objet){
        delete(i);
    }
    for(auto &i : _liste_objet_tot){
        delete(i);
    }

    for(auto &i : _liste_perso){
        delete(i);
    }

}


int Histoire::enVie(){
    int cpt=0;

    for(auto const& i:_liste_perso){
        if(i->getVie()==true)
            cpt++;
    }

    return cpt;
}

float Histoire::getEau(){
    for(auto &i : _liste_objet){
        if(i->getType()==EAU)
            return i->getQuantite();
    }
    return 0;
}

float Histoire::getNourriture(){
    for(auto &i : _liste_objet){
        if(i->getType()==NOURRITURE)
            return i->getQuantite();
    }
    return 0;
}

int Histoire::getSoin(){
    for(auto &i : _liste_objet){
        if(i->getType()==KIT_SOIN)
            return i->getQuantite();
    }
    return 0;
}

void Histoire::setEau(float quantite){
    for(auto &i : _liste_objet){
        if(i->getType()==EAU){
            
            (*i)+=(quantite);
        }
    }
}


void Histoire::setNourriture(float quantite){
    for(auto &i : _liste_objet){
        if(i->getType()==NOURRITURE){
            
            (*i)+=(quantite);
        }
    }
}


//Permet d'initialiser la liste d'objets pour le jeu avec la liste d'objets selectionnés par le joueur au début de la partie
void Histoire::setListeObjet(QList<CustomPixmapItem*> inventaire){

    std::map<Type,int> inventaire_objet;
    std::map<Type,std::string> image_objet;
    std::ofstream fichier("debut_jeu.txt");
    std::ofstream historique("historique.txt", std::ios::app);

    fichier << "Il a fallu faire vite pour se réfugier dans le bunker,\n on retrouve \n";
    historique << "Il a fallu faire vite pour se réfugier dans le bunker, on retrouve ";

    for(auto& i : inventaire)
    {
        if(i->get_type()<12){
            inventaire_objet[i->get_type()]++;
            image_objet[i->get_type()]=i->get_image();
        }
        else{
            if(i->get_type()==PERE){
                Pere *pere = new Pere();
                _liste_perso.push_back(pere);
                fichier  << pere->getNom() << ", le père. \n";
                historique  << pere->getNom() << ", le père. ";
            }
            else if(i->get_type()==MERE){
                Mere *mere = new Mere();
                _liste_perso.push_back(mere);
                fichier  << mere->getNom() << ", la mère. \n";
                historique  << mere->getNom() << ", la mère. ";
            }
            else if(i->get_type()==FILS){
                Fils *fils = new Fils();
                _liste_perso.push_back(fils);
                fichier << fils->getNom() << ", le fils. \n";
                historique << fils->getNom() << ", le fils. ";
            }
            else if(i->get_type()==FILLE){
                Fille *fille = new Fille();
                _liste_perso.push_back(fille);
                fichier <<  fille->getNom() << ", la fille. \n";
                historique << fille->getNom() << ", la fille. ";
            }

        }

    }

    for(auto& i : inventaire_objet){
        for(auto& j : image_objet){
            if(j.first == i.first){
                Objet *objet = new Objet(j.second,i.second,i.first);
                _liste_objet.push_back(objet);
                fichier << objet->getQuantite() << " " << _tab_objet[objet->getType()] << std::endl;
                historique << objet->getQuantite() << " " << _tab_objet[objet->getType()] << std::endl;
            }
        }
    }

    fichier.close();
    historique.close();
}


void Histoire::update_Perso(){
    std::string cause;
    int folie=(_jour%10)+15;

    if(_reduction_stress==true){
        folie=3;
    }


    for(auto& i:_liste_perso){
        
        i->besoins_vitaux(folie);

        /* si il est malade 7j de suite, le personnage meurt */
        if(i->getJourmalade()==7){
            i->setVie(false);
            cause = i->getNom() + " était trop malade pour survivre !!!";
            i->setCausemort(cause);
        }

        /*si un personnage est malade, on incremente le nombre de jours depuis lequel il est malade*/
        if(i->getMaladie()==true){
            i->setJourmalade();
        }

    }

}

/* On initialise la liste totale des objets disponnible dans le jeu */
void Histoire::init_Objet(){

    Objet *nourriture= new Objet(":/bouffe-bunker.png",5,NOURRITURE);
    Objet *eau= new Objet(":/bouteille-eau-bunker.png",5,EAU);
    Objet *kit_soin= new Objet(":/soin-bunker.png",3,KIT_SOIN);
    Objet *radio= new Objet(":/radio-bunker.png",1,RADIO);
    Objet *masque_gaz= new Objet(":/cpp_image.png",1,MASQUE_GAZ);
    Objet *jeux_societe= new Objet(":/jeux-bunker.png",1,JEUX_SOCIETE);
    Objet *lampe_torche= new Objet(":/lampe-bunker.png",1,LAMPE_TORCHE);
    Objet *corde= new Objet(":/corde-bunker.png",1,CORDE);
    Objet *livre= new Objet(":/livre_ferme.png",1,LIVRE);
    Objet *fusil= new Objet(":/fusil-bunker.png",1,FUSIL);
    Objet *hache= new Objet(":/hache-bunker.png",1,HACHE);
    Objet *horloge= new Objet(":/horloge-bunker.png",1,HORLOGE);
    Objet *calendrier= new Objet(":/calendrier-bunker.png",1,CALENDRIER);
    Objet *pere= new Objet(":/pere.png",1,PERE);
    Objet *mere= new Objet(":/mere.png",1,MERE);
    Objet *fils= new Objet(":/fils.png",1,FILS);
    Objet *fille= new Objet(":/fille.png",1,FILLE);


    _liste_objet_tot.push_back(nourriture);
    _liste_objet_tot.push_back(eau);
    _liste_objet_tot.push_back(kit_soin);
    _liste_objet_tot.push_back(radio);
    _liste_objet_tot.push_back(masque_gaz);
    _liste_objet_tot.push_back(jeux_societe);
    _liste_objet_tot.push_back(lampe_torche);
    _liste_objet_tot.push_back(corde);
    _liste_objet_tot.push_back(livre);
    _liste_objet_tot.push_back(fusil);
    _liste_objet_tot.push_back(hache);
    _liste_objet_tot.push_back(horloge);
    _liste_objet_tot.push_back(calendrier);
    _liste_objet_tot.push_back(pere);
    _liste_objet_tot.push_back(mere);
    _liste_objet_tot.push_back(fils);
    _liste_objet_tot.push_back(fille);

}




/* Depart en expedition (depend du personnage qui part et avec quel objet */
void Histoire::expedition(Type perso, Type objet){
    std::ofstream fichier("historique.txt", std::ios::app);
    std::string type;
    std::vector<Objet*> copie_objets;
    std::vector<Objet*> objets_retour;
    bool retour=true;
    std::string cause;


    /*Mise a jour des element de la liste des objets du bunker */
    for(auto& i : _liste_objet){
        if(i->getType()==objet){
            Objet *nv = new Objet(*i);
            copie_objets.push_back(nv);
            
            (*i)-=(1);
            
        }
    }

    if(objet==AUTRE){
        Objet *nv = new Objet(0,AUTRE);
        copie_objets.push_back(nv);
    }

    for(auto& i:_liste_perso){
        type=typeid(*i).name();

        // mettre a jour l'affichage des perso
        //if((type == "class Pere") and (perso==PERE)){
        if((type == "4Pere") and (perso==PERE)){
            /*Le perso pars avec le ventre plein*/
            i->setSoif(i->getSoifmax());
            i->setFaim(i->getFaimmax());

            if(this->getNourriture() - 0.5 >=0){
                this->setNourriture(-0.5);
            }
            if(this->getEau() - 0.5 >= 0){
                this->setEau(-0.5);
            }

            objets_retour=i->partir(&retour,copie_objets);
            


            if(retour==false){
                cause = i->getNom() + " est mort pendant l'expedition !!";
                i->setCausemort(cause);
                deces(i);
            }
            if(objet==AUTRE){
                fichier << i->getNom() << " est parti en expedition avec rien !" << std::endl;
            }
            else{
                fichier << i->getNom() << " est parti en expedition avec 1 " << _tab_objet[objet] <<" !" << std::endl;
            }

            break;
        }

        //else if((type == "class Mere") and (perso==MERE)){
        else if((type == "4Mere") and (perso==MERE)){
            /*Le perso pars avec le ventre plein*/
            i->setSoif(i->getSoifmax());
            i->setFaim(i->getFaimmax());

            if(this->getNourriture() - 0.5 >=0){
                this->setNourriture(-0.5);
            }
            if(this->getEau() - 0.5 >= 0){
                this->setEau(-0.5);
            }

            objets_retour=i->partir(&retour,copie_objets);

            if(retour==false){
                cause = i->getNom() + " est morte pendant l'expedition !!";
                i->setCausemort(cause);
                deces(i);
            }
            std::cout << "La mere est partie" << std::endl;
            if(objet==AUTRE){
                fichier << i->getNom() << " est partie en expedition avec rien !" << std::endl;
            }
            else{
                fichier << i->getNom() << " est partie en expedition avec 1 " << _tab_objet[objet] <<" !" << std::endl;
            }
            break;
        }

        //else if((type == "class Fils") and (perso==FILS)){
        else if((type == "4Fils") and (perso==FILS)){
            /*Le perso pars avec le ventre plein*/
            i->setSoif(i->getSoifmax());
            i->setFaim(i->getFaimmax());

            if(this->getNourriture() - 0.5 >=0){
                this->setNourriture(-0.5);
            }
            if(this->getEau() - 0.5 >= 0){
                this->setEau(-0.5);
            }

            objets_retour=i->partir(&retour,copie_objets);

            if(retour==false){
                cause = i->getNom() + " est mort pendant l'expedition !!";
                i->setCausemort(cause);
                deces(i);
            }
            std::cout << "Le fils est parti" << std::endl;
            if(objet==AUTRE){
                fichier << i->getNom() << " est parti en expedition avec rien !" << std::endl;
            }
            else{
                fichier << i->getNom() << " est parti en expedition avec 1 " << _tab_objet[objet] <<" !" << std::endl;
            }
            break;
        }

        //else if((type == "class Fille") and (perso==FILLE)){
        else if((type == "5Fille") and (perso==FILLE)){
            /*Le perso pars avec le ventre plein*/
            i->setSoif(i->getSoifmax());
            i->setFaim(i->getFaimmax());

            if(this->getNourriture() - 0.5 >=0){
                this->setNourriture(-0.5);
            }
            if(this->getEau() - 0.5 >= 0){
                this->setEau(-0.5);
            }

            objets_retour=i->partir(&retour,copie_objets);

            if(retour==false){
                cause = i->getNom() + " est morte pendant l'expedition !!";
                i->setCausemort(cause);
                deces(i);
            }
            if(objet==AUTRE){
                fichier << i->getNom() << " est partie en expedition avec rien !" << std::endl;
            }
            else{
                fichier << i->getNom() << " est partie en expedition avec 1 " << _tab_objet[objet] <<" !" << std::endl;
            }
            break;
        }

    }

    /*Sauvegarde du jour de départ */
    _depart_expe=_jour;


    /* Si le personnage n'est pas mort */
    if(retour==true){
        /*On recupere les objets recuperer par le personnage pendant son expedition*/
        for(auto& i : objets_retour){

            Objet *nv = new Objet(*i);
            _objet_expe.push_back(nv);

        }

        /* desaloccation memoire */

        for(auto& i : objets_retour){
            delete(i);
        }

    }

    fichier.close();
}

void Histoire::retour_expedition(){
    bool retour=false;
    std::ofstream fichier("expedition.txt", std::ios::out | std::ios::trunc);
    std::ofstream historique("historique.txt", std::ios::app);
    for(auto const& i:_liste_perso){
        // si le perso était en expe
        if(i->getBunker()==false){
            if(_jour == _depart_expe + i->getExpedition()){
                i->setBunker(true);
                retour=true;
                if(fichier && historique){
                    fichier << i->getNom() << " est revenu en vie de son expedition qui a duré " << i->getExpedition() << " jours !!!" << std::endl;
                    historique << i->getNom() << " est revenu en vie de son expedition qui a duré " << i->getExpedition() << " jours !!!" << std::endl;
                }
                break;
            }

        }

    }

    if(retour==true){
        /* Mise a jour de l'inventaire */
        fichier << "L'expedition a été fructueuse : "<< std::endl;
        historique << "L'expedition a été fructueuse : "<< std::endl;
        for (auto& j : _liste_objet)
        {
            for(auto& i : _objet_expe){
                if(j->getType()==i->getType()){
                    (*j)+=(i->getQuantite());
                    
                    if(fichier && historique){

                        fichier << "+ "<< i->getQuantite() << " " << _tab_objet[i->getType()] << std::endl;
                        historique << "+ "<< i->getQuantite() << " " << _tab_objet[i->getType()] << std::endl;
                    }
                }
            }

        }

        for(auto& i : _objet_expe){
            delete(i);

        }
        _objet_expe.clear();
        
    }
    fichier.close();
    historique.close();
}



/* Fonction de rationnement du livre */
void Histoire::rationnement(std::vector<Rationnement> ratio){

    float quantite_nourriture=0;
    float quantite_eau=0;
    int quantite_soin=0;
    int perso=0;

    //on parcourt la liste des perso qui sont dans le bunker, l'ordre est le même que l'ordre du vecteur ratio
    for(auto const& i:_liste_perso){
        if(i->getBunker()==true){

            //en fonction du type de rationnement, on applique des fonctions différentes
            switch(ratio[perso]){
                case manger:
                    i->manger();
                    quantite_nourriture++;

                break;

                case boire:
                    i->boire();
                    quantite_eau++;

                break;

                case manger_boire:
                    i->manger();
                    i->boire();
                    quantite_nourriture++;
                    quantite_eau++;

                break;

                case soin:
                    i->soigner();
                    quantite_soin++;

                break;

                case manger_soin:
                    i->manger();
                    i->soigner();
                    quantite_nourriture++;
                    quantite_soin++;

                break;

                case boire_soin:
                    i->soigner();
                    i->boire();
                    quantite_eau++;
                    quantite_soin++;

                break;

                case manger_boire_soin:
                    i->soigner();
                    i->boire();
                    i->manger();
                    quantite_nourriture++;
                    quantite_eau++;
                    quantite_soin++;

                break;
                default:

                break;
            }
            perso++;
        }

    }
    //Mise a jour de l'inventaire
    this->setNourriture(-(quantite_nourriture/4));
    this->setEau(-(quantite_eau/4));

    for (auto& j : _liste_objet)
    {
        if(j->getType()==KIT_SOIN){
            if(j->getQuantite()-quantite_soin>=0){
             (*j)-=(quantite_soin);
            }
        }

        if(j->getType()==LIVRE || j->getType()==JEUX_SOCIETE || j->getType()==RADIO || j->getType()==CALENDRIER){
            _reduction_stress=true;
        }

    }

}

/* Fonction qui permet de montrer au joueur l'état de ses personnages */
void Histoire::affiche_info(){
    std::ofstream fichier("etat_perso.txt", std::ios::out | std::ios::trunc);
    std::ofstream historique("historique.txt", std::ios::app);
    int flag;
    std::vector<Personnage*> copie;
    copie=_liste_perso;
    if(fichier){
        fichier << "Jour : " << _jour << std::endl;
        fichier << "Informations sur les personnages :" << std::endl;
        historique << "Jour : " << _jour << std::endl;
        historique << "Informations sur les personnages :" << std::endl;
        for(auto & i:copie){
            flag=0;

            if(i->getVie()==false){

                if(i->getBunker()==true){
                    std::cout << i->getCausemort() << std::endl;
                    fichier << i->getCausemort() << std::endl;
                }

                historique << i->getCausemort() << std::endl;
                delete(i);
                _liste_perso.erase(std::remove(_liste_perso.begin(), _liste_perso.end(), i), _liste_perso.end());
                flag=1;

            }
            if(flag==0){
                if(i->getSoif()<=30){
                    fichier << i->getNom() << " a très soif !" << std::endl;
                    historique << i->getNom() << " a très soif !" << std::endl;
                }

                if(i->getSoif()<=50 and i->getSoif()>30){
                    fichier << i->getNom() << " a soif." << std::endl;
                    historique << i->getNom() << " avait soif." << std::endl;
                }


                if(i->getFaim()<=50 and i->getFaim()>30){
                    fichier << i->getNom() << " a faim." << std::endl;
                    historique << i->getNom() << " a faim." << std::endl;

                }
                if(i->getFaim()<=30){
                    fichier << i->getNom() << " a très faim !" << std::endl;
                    historique << i->getNom() << " a très faim !" << std::endl;
                }
                if(i->getMaladie()==true){
                    fichier << i->getNom() << " est malade !" << std::endl;
                    historique << i->getNom() << " est malade !" << std::endl;
                }
                if(i->getSante_mentale()<=50 and i->getSante_mentale()>25 ){
                    fichier << i->getNom() << " commence a agir étrangement." << std::endl;
                    historique << i->getNom() << " commence a agir étrangement." << std::endl;
                }
                if(i->getSante_mentale()<=25 ){
                    fichier << i->getNom() << " a un pete au casque !" << std::endl;
                    historique << i->getNom() << " a un pete au casque !" << std::endl;
                }
                if(i->getBunker()==false){
                    fichier << i->getNom() << " est toujours en expedition." << std::endl;
                    historique << i->getNom() << " est toujours en expedition." << std::endl;
                }
            }

        }
    }
    else{
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    }
    fichier.close();
    historique.close();

}

bool Histoire::getExpedition(){
    for(auto& i : _liste_perso){
        if(i->getBunker()==false){
            return true;
        }
    }
    return false;

}

