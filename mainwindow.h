#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custompixmapitem.h"
#include "besoin.h"
#include "besoin_expedition.h"
#include "perso_expedition.h"
#include "Histoire.hh"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QIcon>
#include <QTimer>
#include <QSize>
#include <QDebug>
#include <QPointF>
#include <QGraphicsTextItem>
#include <QString>
#include <map>
#include <QFile>
#include <QMouseEvent>
#include <cstdlib>
#include <QVector>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    e_Type Type[18]{NOURRITURE,EAU,KIT_SOIN,RADIO,MASQUE_GAZ,
                JEUX_SOCIETE,LAMPE_TORCHE,CORDE,LIVRE,FUSIL,
                HACHE,HORLOGE,CALENDRIER,PERE,MERE,FILS,FILLE,AUTRE};

public:
    MainWindow(QWidget *parent = nullptr);
    void jouer();
    void premier_affichage();
    //void deuxieme_affichage();
    //void troisieme_affichage();
    void affichage_bunker();
    void affichage_items();
    void affichage_livre();
    void affichage_choix_livre(int jour);
    void affichage_expedition(int jour);
    void affichage_scene_nom();
    void fermer_livre();
    void initialisation_item();
    void initialisation_scene();
    void affichage_besoin(int visible);
    void transition_jour();
    void creation_perso();
    void affichage_soin();
    void afficher_menu_expedition(int j=1);
    void affichage_tete_perso(int visible=1);
    void affichage_perso();
    void creation_objet();
    void fin_jeu();
    std::vector<Rationnement> traduction_besoin();
    void mousePressEvent(QMouseEvent* ev);
    void traduction_expedition();
    ~MainWindow();

private slots:
    //void degrader_scene_nom();
    //void degrader_scene_regles();
    void timer_choix();
    void transition_finie();
    void affichage_scene_regles();
    void affichage_scene_inventaire();
    void affichage_quantite();
    void selec_expedition();

private:
    Ui::MainWindow *ui;
    Histoire* _histoire;
    QGraphicsScene* _scene_nom;
    QGraphicsScene* _scene_regles;
    QGraphicsScene* _scene_inventaire;
    QGraphicsScene* _scene_jeu;
    QList<CustomPixmapItem*> _liste_selection;
    QList<CustomPixmapItem*> _liste_inventaire;
    QList<QGraphicsPixmapItem*> _liste_perso;
    QList<QGraphicsPixmapItem*> _liste_icone_perso;
    QList<QGraphicsPixmapItem*> _liste_objet;
    QTimer _t1;
    QTimer _t3;
    QTimer _t_transition;
    QTimer _t_quantite;
    QTimer _t_expedition;
    int opacite=255;
    QGraphicsPixmapItem* _bunker;
    QGraphicsTextItem* _inventaire;
    QGraphicsTextItem* _choix;
    QGraphicsTextItem* _texte_livre;
    QGraphicsTextItem* _texte;
    int _iter=5;
    int _boucle=0;
    bool _livre_ouvert=false;
    int _cpt_fleche=0;
    int _flag_eau=0;
    int _flag_bouffe=0;
    std::map<e_Type,int> _map_besoin;
    QGraphicsPixmapItem* _livre;
    QGraphicsPixmapItem* _fond_noir;
    QGraphicsPixmapItem* _fond_jeu;
    QGraphicsPixmapItem* _fleche;
    QGraphicsPixmapItem* _fleche_regle;
    QList <Besoin*> _bouteille_eau;
    QList <Besoin*> _bouffe;
    QList<Besoin*> _soin;
    QGraphicsPixmapItem* _livre_ferme;
    QGraphicsPixmapItem* _reserve_eau;
    QGraphicsPixmapItem* _reserve_bouffe;
    QGraphicsTextItem* _quantite_eau;
    QGraphicsTextItem* _quantite_bouffe;
    QVector<Perso_expedition*> _expedition_perso;
    QVector<Besoin_expedition*> _expedition_objet;

};
#endif // MAINWINDOW_H
