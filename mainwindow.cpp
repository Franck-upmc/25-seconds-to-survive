#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Définition du nom de la fenêtre
    setWindowTitle("25 SECONDS TO SURVIVE");
    // Définition de l'incone de la fenêtre
    setWindowIcon(QIcon(":/icone.jpg"));

    //Taille fixe de 802 par 417
    setFixedHeight(417);
    setFixedWidth(802);

    srand (time(NULL));
    ui->verticalLayout->setContentsMargins(0,0,0,0);

    //Creation d'une partie
    _histoire= new Histoire;
    _histoire->init_Objet();

    //Debut de la partie
    jouer();
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete _histoire;

    delete _scene_nom;
    delete _scene_regles;
    delete _scene_inventaire;
    delete _scene_jeu;
    /*qDeleteAll(_liste_selection);
    qDeleteAll(_liste_inventaire);
    qDeleteAll(_liste_perso);
    qDeleteAll(_liste_icone_perso);
    qDeleteAll(_liste_objet);
    delete _bunker;
    delete _inventaire;
    delete _choix;
    delete _texte_livre;
    delete _texte;
    delete _livre;
    delete _fond_noir;
    delete _fleche;
    qDeleteAll(_bouteille_eau);
    qDeleteAll(_bouffe);
    qDeleteAll(_soin);
    delete _livre_ferme;
    delete _reserve_eau;
    delete _reserve_bouffe;
    delete _quantite_eau;
    delete _quantite_bouffe;
    qDeleteAll(_expedition_perso);
    qDeleteAll(_expedition_objet);*/

    delete ui;
}

void MainWindow::jouer(){
    //Creation des élements pour réaliser une partie
    initialisation_scene();
    //Affichage du nom du jeu
    affichage_scene_nom();
}

void MainWindow::mousePressEvent(QMouseEvent* ev){
    std::vector<Rationnement> ratio;

    //L'utilisateur a appuyé sur la flèche du livre
    if(ev->pos().x()>560 && ev->pos().x()<580 && ev->pos().y()>340 && ev->pos().y()<360 && _fleche->isVisible()){
        switch(_cpt_fleche){
        case 0:
            affichage_tete_perso(1);
            affichage_choix_livre(_histoire->getJour());
            _cpt_fleche++;
            break;
        case 1:
            affichage_tete_perso(0);
            ratio=traduction_besoin();
            _histoire->rationnement(ratio);

            if(_histoire->getExpedition()){
                affichage_expedition(_histoire->getJour());
                fermer_livre();
                _histoire->nv_jour();
                transition_jour();
                _cpt_fleche=0;

                for(auto& i : _liste_objet){
                    _scene_jeu->removeItem(i);
                }

                for(auto& i : _expedition_objet){
                    _scene_jeu->removeItem(i);
                }

                for(auto& i : _expedition_perso){
                    _scene_jeu->removeItem(i);
                }

                qDeleteAll(_expedition_perso);
                qDeleteAll(_expedition_objet);
                qDeleteAll(_liste_objet);

                _expedition_perso.clear();
                _expedition_objet.clear();
                _liste_objet.clear();

                _histoire->retour_expedition();

                creation_objet();

                for(int i=0;i<_histoire->enVie();i++){
                    Besoin* temp =new Besoin(QPixmap(":/bouteille-eau-vide.png"),0);
                    _scene_jeu->addItem(temp);
                    _bouteille_eau.append(temp);

                    if(i<2){
                        temp->setPos(280 + i*45,215);
                    }
                    else{
                        temp->setPos(380 + i*45,215);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);

                    temp= new Besoin(QPixmap(":/bouffe-vide.png"),1);
                    _scene_jeu->addItem(temp);
                    _bouffe.append(temp);
                    if(i<2){
                        temp->setPos(280 + 20 + i*45,215);
                    }
                    else{
                        temp->setPos(380 + 20 + i*45,215);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);

                    temp= new Besoin(QPixmap(":/soin-vide.png"),2);
                    _scene_jeu->addItem(temp);
                    _soin.append(temp);
                    if(i<2){
                        temp->setPos(280 + 10 + i*45,145);
                    }
                    else{
                        temp->setPos(355 + 10 + i*60,145);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);
                }

                _histoire->update_Perso();

                for(auto& i : _histoire->getListePerso()){
                    i->affiche_info();
                }
                _histoire->affiche_info();

                for(auto& i : _histoire->getListePerso()){
                    i->affiche_info();
                }

                int j=0;
                for(auto& i : _histoire->getListePerso()){
                    if(i->getBunker() && i->getVie()){
                    std::string type=typeid(*i).name();
                    Perso_expedition* temp;
                    std::cout<< " TYPE : "<< type;
                    if(type== "4Pere"){
                        temp= new Perso_expedition(PERE);
                        _expedition_perso.append(temp);
                        _scene_jeu->addItem(temp);
                        if(j<2){
                            temp->setPos(280 + j*60,170);
                        }
                        else{
                            temp->setPos(350 + j*60,170);
                        }
                        temp->setZValue(3);
                        temp->setVisible(false);
                    }
                    else if(type== "4Mere"){
                        temp= new Perso_expedition(MERE);
                        _expedition_perso.append(temp);
                        _scene_jeu->addItem(temp);
                        if(j<2){
                            temp->setPos(280 + j*60,170);
                        }
                        else{
                            temp->setPos(350 + j*60,170);
                        }
                        temp->setZValue(3);
                        temp->setVisible(false);
                    }
                    else if(type == "5Fille"){
                        temp= new Perso_expedition(FILLE);
                        _expedition_perso.append(temp);
                        _scene_jeu->addItem(temp);
                        if(j<2){
                            temp->setPos(280 + j*60,170);
                        }
                        else{
                            temp->setPos(350 + j*60,170);
                        }
                        temp->setZValue(3);
                        temp->setVisible(false);
                    }
                    else {
                        temp= new Perso_expedition(FILS);
                        _expedition_perso.append(temp);
                        _scene_jeu->addItem(temp);
                        if(j<2){
                            temp->setPos(280 + j*60,170);
                        }
                        else{
                            temp->setPos(350 + j*60,170);
                        }
                        temp->setZValue(3);
                        temp->setVisible(false);
                    }
                    j++;
                    }
                }

                affichage_items();

                j=0;
                for(auto& i : _histoire->getListeObjet()){
                    if(i->getQuantite()>0){
                    Besoin_expedition* temp;
                    switch(i->getType()){
                    case  HACHE:
                        temp= new Besoin_expedition(HACHE);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                         break;
                    case MASQUE_GAZ:
                        temp= new Besoin_expedition(MASQUE_GAZ);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                        break;
                    case FUSIL:
                        temp= new Besoin_expedition(FUSIL);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                        break;
                    case LAMPE_TORCHE:
                        temp= new Besoin_expedition(LAMPE_TORCHE);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                        break;
                    case CORDE:
                        temp= new Besoin_expedition(CORDE);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                        break;
                    case RADIO:
                        temp= new Besoin_expedition(RADIO);
                        _expedition_objet.append(temp);
                        _scene_jeu->addItem(temp);
                        temp->setPos(240 + j*55,250);
                        temp->setZValue(3);
                        temp->setVisible(false);
                        j++;
                        break;
                    default:
                        break;
                    }

                   }

                }
                if(_histoire->enVie()==0){
                    fin_jeu();
                }
            }
            else{
                affichage_expedition(_histoire->getJour());
                _cpt_fleche++;
            }
            break;
        case 2:
            fermer_livre();
            traduction_expedition();

            afficher_menu_expedition(0);
            _histoire->nv_jour();

            transition_jour();
            _cpt_fleche=0;

            for(auto& i : _liste_objet){
                _scene_jeu->removeItem(i);
            }

            for(auto& i : _expedition_objet){
                _scene_jeu->removeItem(i);
            }

            for(auto& i : _expedition_perso){
                _scene_jeu->removeItem(i);
            }

            qDeleteAll(_expedition_perso);
            qDeleteAll(_expedition_objet);
            qDeleteAll(_liste_objet);

            _expedition_perso.clear();
            _expedition_objet.clear();
            _liste_objet.clear();

            _histoire->retour_expedition();

            creation_objet();

            for(int i=0;i<_histoire->enVie();i++){
                Besoin* temp =new Besoin(QPixmap(":/bouteille-eau-vide.png"),0);
                _scene_jeu->addItem(temp);
                _bouteille_eau.append(temp);

                if(i<2){
                    temp->setPos(280 + i*45,215);
                }
                else{
                    temp->setPos(380 + i*45,215);
                }
                temp->setZValue(3);
                temp->setVisible(false);

                temp= new Besoin(QPixmap(":/bouffe-vide.png"),1);
                _scene_jeu->addItem(temp);
                _bouffe.append(temp);
                if(i<2){
                    temp->setPos(280 + 20 + i*45,215);
                }
                else{
                    temp->setPos(380 + 20 + i*45,215);
                }
                temp->setZValue(3);
                temp->setVisible(false);

                temp= new Besoin(QPixmap(":/soin-vide.png"),2);
                _scene_jeu->addItem(temp);
                _soin.append(temp);
                if(i<2){
                    temp->setPos(280 + 10 + i*45,145);
                }
                else{
                    temp->setPos(355 + 10 + i*60,145);
                }
                temp->setZValue(3);
                temp->setVisible(false);
            }

            _histoire->update_Perso();

            for(auto& i : _histoire->getListePerso()){
                i->affiche_info();
            }
            _histoire->affiche_info();

            for(auto& i : _histoire->getListePerso()){
                i->affiche_info();
            }

            int j=0;
            for(auto& i : _histoire->getListePerso()){
                if(i->getBunker() && i->getVie()){
                std::string type=typeid(*i).name();
                Perso_expedition* temp;
                std::cout<< " TYPE : "<< type;
                if(type== "4Pere"){
                    temp= new Perso_expedition(PERE);
                    _expedition_perso.append(temp);
                    _scene_jeu->addItem(temp);
                    if(j<2){
                        temp->setPos(280 + j*60,170);
                    }
                    else{
                        temp->setPos(350 + j*60,170);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);
                }
                else if(type== "4Mere"){
                    temp= new Perso_expedition(MERE);
                    _expedition_perso.append(temp);
                    _scene_jeu->addItem(temp);
                    if(j<2){
                        temp->setPos(280 + j*60,170);
                    }
                    else{
                        temp->setPos(350 + j*60,170);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);
                }
                else if(type == "5Fille"){
                    temp= new Perso_expedition(FILLE);
                    _expedition_perso.append(temp);
                    _scene_jeu->addItem(temp);
                    if(j<2){
                        temp->setPos(280 + j*60,170);
                    }
                    else{
                        temp->setPos(350 + j*60,170);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);
                }
                else {
                    temp= new Perso_expedition(FILS);
                    _expedition_perso.append(temp);
                    _scene_jeu->addItem(temp);
                    if(j<2){
                        temp->setPos(280 + j*60,170);
                    }
                    else{
                        temp->setPos(350 + j*60,170);
                    }
                    temp->setZValue(3);
                    temp->setVisible(false);
                }
                j++;
                }
            }

            affichage_items();

            j=0;
            for(auto& i : _histoire->getListeObjet()){
                if(i->getQuantite()>0){
                Besoin_expedition* temp;
                switch(i->getType()){
                case  HACHE:
                    temp= new Besoin_expedition(HACHE);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                     break;
                case MASQUE_GAZ:
                    temp= new Besoin_expedition(MASQUE_GAZ);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                    break;
                case FUSIL:
                    temp= new Besoin_expedition(FUSIL);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                    break;
                case LAMPE_TORCHE:
                    temp= new Besoin_expedition(LAMPE_TORCHE);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                    break;
                case CORDE:
                    temp= new Besoin_expedition(CORDE);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                    break;
                case RADIO:
                    temp= new Besoin_expedition(RADIO);
                    _expedition_objet.append(temp);
                    _scene_jeu->addItem(temp);
                    temp->setPos(240 + j*55,250);
                    temp->setZValue(3);
                    temp->setVisible(false);
                     j++;
                    break;
                default:
                    break;
                }

               }

            }
            if(_histoire->enVie()==0){
                fin_jeu();
            }
            break;
        }


    }
    //L'utilisateur a apppuyé sur le livre
    else if(ev->pos().x()>0 && ev->pos().x()<50 && ev->pos().y()>0 && ev->pos().y()<50 && !_livre_ouvert){
        _livre_ouvert=true;
        affichage_livre();
    }
    //L'utilisateur a appuyé sur la fleche pour accéder à la sélection de l'inventaire
    else if(ev->pos().x()>750 && ev->pos().x()<(750+30) && ev->pos().y()>370 && ev->pos().y()<(370+25) && _fleche_regle->isVisible()){
        affichage_scene_inventaire();
    }


}

void MainWindow::timer_choix(){

    for(auto& i :_liste_selection){
        if(i->get_in_inventaire()){
            _liste_inventaire.push_back(i);
            _liste_selection.removeOne(i);

        }
    }
    if(_boucle==5){
        _t3.stop();
        affichage_bunker();
    }
    else{
        if(_iter>0){
            _choix->setPlainText(QString("Faites votre choix : " + QString::number(_iter)));
            _iter--;
        }
        else{
            int t,j=0;
            for(int i=_liste_selection.first()->get_cpt();i>0;i--){
                std::vector<Objet*> l=_histoire->getListeObjet_tot();
                t=rand()%13;
                while(l[t]->getQuantite()<1.0){
                    t=rand()%13;
                }

                l[t]->setQuantite(l[t]->getQuantite()-1.0);
                CustomPixmapItem* temp=new CustomPixmapItem(Type[t]);
                _liste_selection.append(temp);
                _scene_inventaire->addItem(temp);
                temp->setZValue(2);
                j++;
            }

            j=0;
            for(auto& i: _liste_selection){
                i->setPos(35 + j*150,160);
                j++;
            }

            _liste_inventaire.first()->set_cpt(0);

            _boucle++;
            _iter=5;
        }
    }
}

//On affiche le bunker avec les différents personnages et objets
void MainWindow::affichage_bunker(){
    ui->graphicsView->setScene(_scene_jeu);
    ui->verticalLayout->setContentsMargins(0,0,0,0);

    _histoire->setListeObjet(_liste_inventaire);

    initialisation_item();

    creation_objet();


    _scene_jeu->addItem(_fond_noir);
    _fond_noir->setZValue(3);
    _fond_noir->setVisible(false);

    _scene_jeu->addItem(_texte);
    _fond_noir->setZValue(3);
    _fond_noir->setVisible(false);

    QFont f;
    f.setPixelSize(23);
    f.setBold(true);
    _texte->setFont(f);
    _texte->setVisible(false);

    creation_perso();
    affichage_items();
}

void MainWindow::affichage_items(){
    affichage_perso();
}

//On affiche le livre avec les informations sur les personnages
void MainWindow::affichage_livre(){

    QFile file("etat_perso.txt");

    if(_histoire->getJour()==0){
        file.setFileName("debut_jeu.txt");
    }

    QString strings;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            strings += "\n" + in.readLine();
        }
    }

    _texte_livre= new QGraphicsTextItem(strings);
    _texte_livre->setPos(250,65);
    _scene_jeu->addItem(_texte_livre);
    _texte_livre->setVisible(true);
    _texte_livre->setZValue(2);

    _livre->setVisible(true);
    _livre->setZValue(1);

    _fleche->setVisible(true);
    _fleche->setZValue(2);




}

//On permet au joueur de pouvoir nourrir, hydrater ou soigner ses personnages
void MainWindow::affichage_choix_livre(int jour){
    qDebug()<<"Affichage choix livre";

    QString strings;
    strings="              Jour " + QString::number(jour) + "\n\n" + "Rationnons les ressources ... \n\n\n\n\n\n";

    connect(&_t_quantite,SIGNAL(timeout()),this,SLOT(affichage_quantite()));

    _bouteille_eau.first()->set_quantite_eau(_histoire->getEau());
    _bouffe.first()->set_quantite_bouffe(_histoire->getNourriture());
    _soin.first()->set_quantite_soin(_histoire->getSoin());

    _t_quantite.start(10);

    _reserve_eau->setVisible(true);
    _reserve_eau->setZValue(2);
    _quantite_eau->setVisible(true);
    _quantite_eau->setZValue(2);
    _reserve_bouffe->setVisible(true);
    _reserve_bouffe->setZValue(2);
    _quantite_bouffe->setVisible(true);
    _quantite_bouffe->setZValue(2);

    affichage_besoin(1);

    _texte_livre->setPlainText(strings);

}

//On laisse le choix au joueur de pouvoir partir enexpédition avec un personnage et/ou un objet
void MainWindow::affichage_expedition(int jour){
    qDebug()<<"Affichage expedition";

    _t_quantite.stop();

    _reserve_eau->setVisible(false);
    _reserve_bouffe->setVisible(false);

    _quantite_eau->setVisible(false);
    _quantite_bouffe->setVisible(false);

    for(auto& i : _expedition_perso){
        i->setVisible(true);
    }

    for(auto& i : _expedition_objet){
        i->setVisible(true);
    }

    for(auto& k : _expedition_objet){
        k->setVisible(true);
    }

    for(auto& i : _bouteille_eau){
        i->reset();
    }

    for(auto& i : _bouffe){
        i->reset();
    }
    affichage_besoin(0);

    QString s="                Jour " + QString::number(jour) + "\n\n\n Partir en expedition";
    _texte_livre->setPlainText(s);

    connect(&_t_expedition,SIGNAL(timeout()),this,SLOT(selec_expedition()));

    _t_expedition.start(50);

}

//La jounée est terminée, on ferme le livre pour le jour suivant
void MainWindow::fermer_livre(){
    qDebug()<<"Livre se ferme";

    _livre->setVisible(false);
    _fleche->setVisible(false);
    _texte_livre->setVisible(false);
    _livre_ouvert=false;
}

//On initialise les différentes scènes du jeu
void MainWindow::initialisation_scene(){
    _scene_nom= new QGraphicsScene;

    _scene_regles=new QGraphicsScene;

    _scene_inventaire=new QGraphicsScene;

    _scene_jeu=new QGraphicsScene;
}

//On affiche la couverture du jeu "25 SECONDS TO SURVIVE"
void MainWindow::affichage_scene_nom(){
    _fond_noir=new QGraphicsPixmapItem(QPixmap(":/fond-noir.jpg"));
    _fond_jeu= new QGraphicsPixmapItem(QPixmap(":/page_de_garde_25_s.jpg"));
    _scene_nom->addItem(_fond_jeu);

    _texte=new QGraphicsTextItem;
    _texte->setDefaultTextColor(QColor(Qt::white));
    _texte->setZValue(1);
    _scene_nom->addItem(_texte);

    QFont f;
    f.setPixelSize(20);
    f.setBold(true);
    _texte->setFont(f);
    //_texte->setPlainText("There\nIs\nNo\nPlanet\nB");*/

    ui->graphicsView->setScene(_scene_nom);

    connect(&_t1,SIGNAL(timeout()),this,SLOT(affichage_scene_regles()));

    //Affichage de 4 secondes
    _t1.start(4000);

}

//On introduit le contexte et les règles du jeu
void MainWindow::affichage_scene_regles(){
    _t1.stop();

    _fleche_regle=new QGraphicsPixmapItem(QPixmap(":/fleche_blanche.jpg"));
    _fleche_regle->setPos(750,370);
    _fleche_regle->setZValue(4);
    _scene_regles->addItem(_fleche_regle);


    _scene_regles->addItem(_fond_noir);
    _scene_regles->addItem(_texte);
    _texte->setPlainText("Nous sommes le 19 mai 2060 et un nuage radioactif mortel est sur le point\nd'atteindre la maison dans laquelle vous habitez avec votre femme et\nvos 2 enfants.\nVous incarnez le rôle du père et vous avez 25 secondes pour récupérer un\nmaximum d'objets dans votre maison avant de vous enfermer dans le bunker\nde votre jardin. Dans quelques instants, vous aurez 5 secondes pour sélectionner\n2 objets parmi la liste d'objet et de personnage qui s'affichera devant vous.\nChoisissez bien, l'objectif est de survivre le plus longtemps possible, privilégiez\ndonc la nourriture et l'eau. Les objets ont aussi un rôle important car vous pourrez\nles emporter en expédition pour espérer pouvoir ramener des objets trouvés à\nl'extérieur. Ensuite, lorsque vous serez dans le bunker, vous devrez suivre les\nindications en cliquant sur le petit livre en haut à gauche de votre écran.\nSoyez rapide et consciencieux pour le début de la fin...");

    ui->graphicsView->setScene(_scene_regles);

}

//Le joueur choisi les objets qu'il va utiliser pendant la partie
void MainWindow::affichage_scene_inventaire(){
    delete _fleche_regle;

    QFont f;
    f.setPointSize(20);
    f.setBold(true);

    _inventaire=new QGraphicsTextItem(QString("Inventaire"));
    _choix=new QGraphicsTextItem(QString("Faites votre choix : "));

    _choix->setFont(f);
    _choix->setDefaultTextColor(Qt::white);
    _inventaire->setFont(f);
    _inventaire->setDefaultTextColor(Qt::white);
    _inventaire->setPos(290,250);
    _choix->setPos(220,60);
    _choix->setZValue(1);
    _inventaire->setZValue(1);

    _scene_inventaire->addItem(_inventaire);
    _scene_inventaire->addItem(_fond_noir);
    _scene_inventaire->addItem(_choix);

    // Le père est un personnage obligatoire

    CustomPixmapItem* t=new CustomPixmapItem(PERE);
    _liste_inventaire.append(t);
    _scene_inventaire->addItem(t);
    t->setZValue(2);
    t->setPos(20,330);

    // Selection des 3 personnages restants

    for(int i=0;i<3;i++){
        CustomPixmapItem* temp=new CustomPixmapItem(Type[14+i] );
        temp->setPos(35 + i*150,180);
        temp->setZValue(2);
        _liste_selection.append(temp);
        _scene_inventaire->addItem(temp);
    }

    //On ajoute une bouteille d'eau et une nourriture

    CustomPixmapItem* temp=new CustomPixmapItem(EAU);
    temp->setPos(35 + 3*150,180);
    temp->setZValue(2);
    _liste_selection.append(temp);
    _scene_inventaire->addItem(temp);

    temp=new CustomPixmapItem(NOURRITURE );
    temp->setPos(35 + 4*150,180);
    temp->setZValue(2);
    _liste_selection.append(temp);
    _scene_inventaire->addItem(temp);


    _t3.start(1000);
    connect(&_t3,SIGNAL(timeout()),this,SLOT(timer_choix()));


    ui->graphicsView->setScene(_scene_inventaire);

}

//On initialise la majorité des élements graphiques qu'on va utiliser pendant la partie
void MainWindow::initialisation_item(){

    _bunker = new QGraphicsPixmapItem(QPixmap(":/bunker.png"));
    _scene_jeu->addItem(_bunker);

    _reserve_eau= new QGraphicsPixmapItem(QPixmap(":/bouteille-eau.png"));
    _scene_jeu->addItem(_reserve_eau);
    _reserve_eau->setPos(450,290);
    _reserve_eau->setVisible(false);

    _reserve_bouffe= new QGraphicsPixmapItem(QPixmap(":/bouffe.png"));
    _scene_jeu->addItem(_reserve_bouffe);
    _reserve_bouffe->setPos(450,310);
    _reserve_bouffe->setVisible(false);

    _quantite_eau = new QGraphicsTextItem;
    _scene_jeu->addItem(_quantite_eau);
    _quantite_eau->setPos(480,290);
    _quantite_eau->setVisible(false);

    _quantite_bouffe = new QGraphicsTextItem;
    _scene_jeu->addItem(_quantite_bouffe);
    _quantite_bouffe->setPos(480,310);
    _quantite_bouffe->setVisible(false);

    _livre=new QGraphicsPixmapItem(QPixmap(":/livre.png"));
    _scene_jeu->addItem(_livre);
    _livre->setPos(200,50);
    _livre->setVisible(false);

    _fleche=new QGraphicsPixmapItem(QPixmap(":/fleche_droite.png"));
    _scene_jeu->addItem(_fleche);
    _fleche->setPos(560,340);
    _fleche->setVisible(false);

    _livre_ferme=new QGraphicsPixmapItem(QPixmap(":/livre_ferme.png"));;
    _scene_jeu->addItem(_livre_ferme);
    _livre_ferme->setPos(0,0);

    for(int i=0;i<_histoire->enVie();i++){
        Besoin* temp =new Besoin(QPixmap(":/bouteille-eau-vide.png"),0);
        _scene_jeu->addItem(temp);
        _bouteille_eau.append(temp);

        if(i<2){
            temp->setPos(280 + i*45,215);
        }
        else{
            temp->setPos(380 + i*45,215);
        }
        temp->setZValue(3);
        temp->setVisible(false);

        temp= new Besoin(QPixmap(":/bouffe-vide.png"),1);
        _scene_jeu->addItem(temp);
        _bouffe.append(temp);
        if(i<2){
            temp->setPos(280 + 20 + i*45,215);
        }
        else{
            temp->setPos(380 + 20 + i*45,215);
        }
        temp->setZValue(3);
        temp->setVisible(false);

        temp= new Besoin(QPixmap(":/soin-vide.png"),2);
        _scene_jeu->addItem(temp);
        _soin.append(temp);
        if(i<2){
            temp->setPos(280 + 10 + i*45,145);
        }
        else{
            temp->setPos(355 + 10 + i*60,145);
        }
        temp->setZValue(3);
        temp->setVisible(false);
    }

    int j=0;
    for(auto& i : _histoire->getListePerso()){
        std::string type=typeid(*i).name();
        Perso_expedition* temp;
        std::cout<< " TYPE : "<< type;
        if(type== "4Pere"){
            temp= new Perso_expedition(PERE);
            _expedition_perso.append(temp);
            _scene_jeu->addItem(temp);
            if(j<2){
                temp->setPos(280 + j*60,170);
            }
            else{
                temp->setPos(350 + j*60,170);
            }
            temp->setZValue(3);
            temp->setVisible(false);
        }
        else if(type== "4Mere"){
            temp= new Perso_expedition(MERE);
            _expedition_perso.append(temp);
            _scene_jeu->addItem(temp);
            if(j<2){
                temp->setPos(280 + j*60,170);
            }
            else{
                temp->setPos(350 + j*60,170);
            }
            temp->setZValue(3);
            temp->setVisible(false);
        }
        else if(type == "5Fille"){
            temp= new Perso_expedition(FILLE);
            _expedition_perso.append(temp);
            _scene_jeu->addItem(temp);
            if(j<2){
                temp->setPos(280 + j*60,170);
            }
            else{
                temp->setPos(350 + j*60,170);
            }
            temp->setZValue(3);
            temp->setVisible(false);
        }
        else {
            temp= new Perso_expedition(FILS);
            _expedition_perso.append(temp);
            _scene_jeu->addItem(temp);
            if(j<2){
                temp->setPos(280 + j*60,170);
            }
            else{
                temp->setPos(350 + j*60,170);
            }
            temp->setZValue(3);
            temp->setVisible(false);
        }
        j++;
    }

    j=0;
    for(auto& i : _histoire->getListeObjet()){
        Besoin_expedition* temp;
        switch(i->getType()){
        case  HACHE:
            temp= new Besoin_expedition(HACHE);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
             break;
        case MASQUE_GAZ:
            temp= new Besoin_expedition(MASQUE_GAZ);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
            break;
        case FUSIL:
            temp= new Besoin_expedition(FUSIL);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
            break;
        case LAMPE_TORCHE:
            temp= new Besoin_expedition(LAMPE_TORCHE);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
            break;
        case CORDE:
            temp= new Besoin_expedition(CORDE);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
            break;
        case RADIO:
            temp= new Besoin_expedition(RADIO);
            _expedition_objet.append(temp);
            _scene_jeu->addItem(temp);
            temp->setPos(240 + j*55,250);
            temp->setZValue(3);
            temp->setVisible(false);
            j++;
            break;
        default:
            break;
        }


    }

}

//On affiche un écran noir avec le jour suivant pour signaler qu'on change de jour
void MainWindow::transition_jour(){
    _fond_noir->setVisible(true);
    _texte->setPlainText("Jour " + QString::number(_histoire->getJour()));
    _texte->setVisible(true);
    _texte->setZValue(3);
    _texte->setPos(370,190);

    connect(&_t_transition,SIGNAL(timeout()),this,SLOT(transition_finie()));

    _t_transition.start(2000);
}

//La transition journalière est finie
void MainWindow::transition_finie(){
    _t_transition.stop();
    _fond_noir->setVisible(false);
    _texte->setVisible(false);
}

//On affiche les besoins des personnages si visible est différent de 0, sinon on les cache
void MainWindow::affichage_besoin(int visible){

    for(auto& i : _soin){
        i->setVisible(false);
    }

    for(auto& i : _bouteille_eau){
        i->setVisible(false);
    }

    for(auto& i : _bouffe){
        i->setVisible(false);
    }

    if(visible){
        int iter=0;
       for(auto& i : _histoire->getListePerso()){
           if(i->getBunker() && i->getVie()){
                _bouteille_eau[iter]->setVisible(true);
                 _bouffe[iter]->setVisible(true);


            }
        iter++;
       }
       int n_soin=0;
       for(auto& i : _histoire->getListePerso()){
           if(i->getMaladie() && i->getBunker()){
               _soin[n_soin]->setVisible(true);

           }
           n_soin++;
       }
    }
}

//On affiche les personnages en vie et présent dans le bunker
void MainWindow::affichage_perso(){

     // On cache tous les personnages
     for(auto& k : _liste_perso){
         k->setVisible(false);
     }

    // On affiche les personnages vivants et dans le bunker
    int i=0;
    for(auto& j : _histoire->getListePerso()){
        if(j->getBunker()){
             _liste_perso[i]->setVisible(true);
             _liste_perso[i]->setPixmap(QPixmap(QString::fromStdString(j->getImage())));
        }
        i++;
    }

}

//On affiche la tete des personnages dans l'écran de sélection s'ils sont en vie et dans le bunker
void MainWindow::affichage_tete_perso(int visible){
    //On cache tous les personnages
    for(auto& i : _liste_icone_perso){
        i->setVisible(false);
    }

    //On affiche les personnages en vie et dans le bunker
    if(visible==1){
        int i=0;
        for(auto& j : _histoire->getListePerso()){
            if(j->getVie() && j->getBunker()){
                _liste_icone_perso[i]->setVisible(true);
                _liste_icone_perso[i]->setPixmap(QPixmap(QString::fromStdString(j->getImageTete())));
            }
            i++;
        }
    }

}


void MainWindow::creation_perso(){

     //On crée les personnages à afficher en fonction des personnages en vie
     int pos=0;
     for(auto& i : _histoire->getListePerso()){
           QGraphicsPixmapItem * temp= new QGraphicsPixmapItem(QPixmap(QString::fromStdString(i->getImage())));
           _scene_jeu->addItem(temp);
           _liste_perso.append(temp);
           temp->setPos(250 + pos*100,110);
           temp->setZValue(0);
           temp->setVisible(false);
           pos++;
      }

      pos=0;
      int increment=0;
      //On crée les icones des personnages à afficher en fonction des personnages en vie
      for(auto& i : _histoire->getListePerso()){
          QGraphicsPixmapItem * temp= new QGraphicsPixmapItem(QPixmap(QString::fromStdString(i->getImageTete())));
          _scene_jeu->addItem(temp);
          _liste_icone_perso.append(temp);
          if(increment<2){
              temp->setPos(280 + pos*60,170);
          }
          else {
              temp->setPos(350 + pos*60,170);
          }
          increment++;
          temp->setZValue(4);
          temp->setVisible(false);
          pos++;

     }
}

std::vector<Rationnement> MainWindow::traduction_besoin(){
    std::vector<Rationnement> _vector_besoin;
    for(int iter=0; iter< (int) _histoire->getListePerso().size();iter++){
        if(_bouteille_eau[iter]->isVisible()){
            if(_bouteille_eau[iter]->get_flag() && !_bouffe[iter]->get_flag() && !_soin[iter]->get_flag()){
                _vector_besoin.push_back(boire);
            }
            else if(_bouteille_eau[iter]->get_flag() && _bouffe[iter]->get_flag() && !_soin[iter]->get_flag()){
                _vector_besoin.push_back(manger_boire);
            }
            else if(!_bouteille_eau[iter]->get_flag() && _bouffe[iter]->get_flag() && !_soin[iter]->get_flag()){
                _vector_besoin.push_back(manger);
            }
            else if(_bouteille_eau[iter]->get_flag() && !_bouffe[iter]->get_flag() && _soin[iter]->get_flag()){
                _vector_besoin.push_back(boire_soin);
            }
            else if(!_bouteille_eau[iter]->get_flag() && _bouffe[iter]->get_flag() && _soin[iter]->get_flag()){
                _vector_besoin.push_back(manger_soin);
            }
            else if(!_bouteille_eau[iter]->get_flag() && !_bouffe[iter]->get_flag() && _soin[iter]->get_flag()){
                _vector_besoin.push_back(soin);
            }
            else if(_bouteille_eau[iter]->get_flag() && _bouffe[iter]->get_flag() && _soin[iter]->get_flag()){
                _vector_besoin.push_back(manger_boire_soin);
            }
            else {
                _vector_besoin.push_back(rien);
            }
       }
    }
    return _vector_besoin;
}

//On met à jour la quantité de nourriture et d'eau en fonction des choix du joueur en temps réel
void MainWindow::affichage_quantite(){
    _quantite_eau->setPlainText(QString::number(_bouteille_eau.first()->get_quantite_eau()));
    _quantite_bouffe->setPlainText(QString::number(_bouteille_eau.first()->get_quantite_bouffe()));
}

void MainWindow::affichage_soin(){
    int j=0;
    for(auto& i : _soin){
        i->setVisible(true);
        j++;
    }
}

//On remet à zero les choix d'expedition du joueur pour préparer le tour suivant
void MainWindow::selec_expedition(){
    for(auto& i : _expedition_objet){
        if(i->get_push()!=i->get_p()){
            i->reset();
        }
    }
    for(auto& i : _expedition_perso){
        if(i->get_push()!=i->get_p()){
            i->reset();
        }
    }
}

//Si j=1 on affiche le menu d'expédition, sinon on ne l'affiche pas
void MainWindow::afficher_menu_expedition(int j){
    if(j==1){
        for(auto& i : _expedition_perso){
            i->setVisible(true);
        }
        for(auto& i : _expedition_objet){
            i->setVisible(true);
        }
    }
    else{
        for(auto& i : _expedition_perso){
            i->setVisible(false);
            i->reset();
        }
        for(auto& i : _expedition_objet){
            i->setVisible(false);
            i->reset();
        }
    }
}

//On crée toutes les images des objets présents dans le bunker
void MainWindow::creation_objet(){
    int pos_eau=0;
    int pos_bouffe=0;
    int flag_masque_gaz=0;
    for(auto& i : _histoire->getListeObjet()){
        if(i->getQuantite()>0){

        QGraphicsPixmapItem* temp= new QGraphicsPixmapItem(QPixmap(QString::fromStdString(i->getImage())));
        temp->setVisible(true);
        temp->setZValue(0);
        _liste_objet.append(temp);
        _scene_jeu->addItem(temp);

        switch(i->getType()){
        case EAU:
            pos_eau=round(i->getQuantite());
            temp->setPos(600 + 25*pos_eau,32);
            pos_eau--;
            while(pos_eau>0){
                temp=new QGraphicsPixmapItem(QPixmap(QString::fromStdString(i->getImage())));
                temp->setVisible(true);
                temp->setZValue(0);
                _liste_objet.append(temp);
                _scene_jeu->addItem(temp);
                temp->setPos(600 + 25*pos_eau,32);
                pos_eau--;
            }
            break;
        case NOURRITURE:
            pos_bouffe=round(i->getQuantite());
            temp->setPos(-34 + 40*pos_bouffe,350);
             pos_bouffe--;
            while(pos_bouffe>0){
                temp=new QGraphicsPixmapItem(QPixmap(QString::fromStdString(i->getImage())));
                temp->setVisible(true);
                temp->setZValue(0);
                _liste_objet.append(temp);
                _scene_jeu->addItem(temp);
                temp->setPos(-34 + 40*pos_bouffe,350);
                pos_bouffe--;
            }


            break;
        case HACHE:
            temp->setPos(675,260);
            break;
        case MASQUE_GAZ:
            flag_masque_gaz=1;
            temp->setVisible(false);
            break;
        case JEUX_SOCIETE:
            temp->setPos(135,272);
            break;
        case CALENDRIER:
            temp->setPos(197,139);
            break;
        case LIVRE:
            temp->setPos(65,260);
            break;
        case CORDE:
            temp->setPos(150,346);
            break;
        case LAMPE_TORCHE:
            temp->setPos(23,282);
            break;
        case RADIO:
            temp->setPos(490,30);
            break;
        case KIT_SOIN:
            temp->setPos(477,50);
            break;
        case HORLOGE:
            temp->setPos(408,27);
            break;
        case FUSIL:
            temp->setPos(728,260);
            break;
        default:
            break;
        }
    }
}
    if(flag_masque_gaz==0){
        QGraphicsPixmapItem* temp=new QGraphicsPixmapItem(QPixmap(":/cpp_image.png"));
        temp->setVisible(true);
        temp->setZValue(0);
        temp->setPos(40,115);
        _liste_objet.append(temp);
        _scene_jeu->addItem(temp);
    }
}

//Prise en compte des choix d'expedition du joueur
void MainWindow::traduction_expedition(){
    e_Type perso;
    e_Type objet=AUTRE;
    bool flag_expedition=false;
    for(auto& i : _expedition_perso){
        if(i->get_pick()){
            perso=i->get_type();
            flag_expedition=true;
        }
    }
    for(auto& i : _expedition_objet){
        if(i->get_pick()){
            objet=i->get_type();
        }
    }

    if(flag_expedition){
        _histoire->expedition(perso,objet);
    }
    else{
        qDebug()<< "PAS D'EXPEDITION";
    }

}

//Le jeu est fini, on affiche l'écran de fin
void MainWindow::fin_jeu(){
    _fond_noir->setVisible(true);
    _texte->setVisible(true);
    _texte->setPlainText("FIN");
    _t_transition.stop();
}
