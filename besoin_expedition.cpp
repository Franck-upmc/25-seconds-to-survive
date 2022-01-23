#include "besoin_expedition.h"

int Besoin_expedition::p=0;

void Besoin_expedition::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    if(!_pick){
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

Besoin_expedition::Besoin_expedition(e_Type type, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    _type=type;
    image_vide();
}

void Besoin_expedition::reset(){
    _pick=0;
    image_vide();
}

void Besoin_expedition::image_pleine(){
    switch(_type){
    case HACHE:
        setPixmap(QPixmap(":/hache-bunker.png").scaled(50,50));
        break;
    case FUSIL:
        setPixmap(QPixmap(":/fusil-bunker.png").scaled(50,50));
        break;
    case LAMPE_TORCHE:
        setPixmap(QPixmap(":/lampe-bunker.png").scaled(50,50));
        break;
    case RADIO:
        setPixmap(QPixmap(":/radio-bunker.png").scaled(50,50));
        break;
    case MASQUE_GAZ:
        setPixmap(QPixmap(":/masque_gaz.png").scaled(50,50));
        break;
    case CORDE:
        setPixmap(QPixmap(":/corde-bunker.png").scaled(50,50));
        break;
    default:
        break;
    }
}

void Besoin_expedition::image_vide(){
    switch(_type){
    case HACHE:
        setPixmap(QPixmap(":/hache_vide.png").scaled(50,50));
        break;
    case FUSIL:
        setPixmap(QPixmap(":/fusil_vide.png").scaled(50,50));
        break;
    case LAMPE_TORCHE:
        setPixmap(QPixmap(":/lampe_vide.png").scaled(50,50));
        break;
    case RADIO:
        setPixmap(QPixmap(":/radio_vide.png").scaled(50,50));
        break;
    case MASQUE_GAZ:
        setPixmap(QPixmap(":/masque_vide.png").scaled(50,50));
        break;
    case CORDE:
        setPixmap(QPixmap(":/corde_vide.png").scaled(50,50));
        break;
    default:
        break;
    }
}
