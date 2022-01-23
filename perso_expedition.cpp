#include "perso_expedition.h"

int Perso_expedition::p=0;

Perso_expedition::Perso_expedition(e_Type type, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    _type=type;
    image_vide();

}

void Perso_expedition::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    qDebug()<<event->pos();
    if(_pick==0){
        image_pleine();
        _pick=1;
        p=p+1;
        _push=p;
    }
    else{
        image_vide();
        _pick=0;
    }
}
void Perso_expedition::reset(){
    _pick=0;
    image_vide();
}

void Perso_expedition::image_vide(){
    switch(_type){
    case PERE:
        setPixmap(QPixmap(":/pere_tete_vide.png"));
        break;
    case MERE:
        setPixmap(QPixmap(":/mere_tete_vide.png"));
        break;
    case FILS:
        setPixmap(QPixmap(":/fils_tete_vide.png"));
        break;
    case FILLE:
        setPixmap(QPixmap(":/fille_tete_vide.png"));
        break;
    default:
        break;
    }
}

void Perso_expedition::image_pleine(){
    switch(_type){
    case PERE:
        setPixmap(QPixmap(":/pere_tete.png"));
        break;
    case MERE:
        setPixmap(QPixmap(":/mere_tete.png"));
        break;
    case FILS:
        setPixmap(QPixmap(":/fils_tete.png"));
        break;
    case FILLE:
        setPixmap(QPixmap(":/fille_tete.png"));
        break;
    default:

        break;
    }
}





