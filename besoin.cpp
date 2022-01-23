#include "besoin.h"

float Besoin::quantite_eau = (float)4.0;
float Besoin::quantite_bouffe = (float)4.0;
int Besoin::quantite_soin = 4;

Besoin::Besoin(const QPixmap &pixmap,int t, QGraphicsItem *parent): QGraphicsPixmapItem(pixmap,parent){
    _t=t;
    switch(t){
    case 0:
        _show=":/bouteille-eau-vide.png";
        break;
    case 1:
        _show=":/bouffe-vide.png";
        break;
    case 2:
        _show=":/soin-vide.png";
        break;
    }
}

void Besoin::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    switch(_t){
    case 0:
        if(!_flag && quantite_eau>0.0){
            setPixmap(QPixmap(":/bouteille-eau.png"));
            _flag=1;
            quantite_eau=quantite_eau-0.25;
        }
        else if(!_flag && quantite_eau==0){
            //Ne rien faire
        }
        else if(_flag==1){
            setPixmap(QPixmap(":/bouteille-eau-vide.png"));
            _flag=0;
            quantite_eau=quantite_eau+0.25;
        }
        break;
    case 1:
        if(!_flag && quantite_bouffe){
            setPixmap(QPixmap(":/bouffe.png"));
            _flag=1;
            quantite_bouffe=quantite_bouffe-0.25;
        }
        else if(!_flag && quantite_bouffe==0){
            //Ne rien faire
        }
        else{
            setPixmap(QPixmap(":/bouffe-vide.png"));
            _flag=0;
            quantite_bouffe=quantite_bouffe+0.25;
        }
        break;
    case 2:
        if(!_flag && quantite_soin){
            setPixmap(QPixmap(":/soin.png"));
            _flag=1;
            quantite_soin=quantite_soin-1;
        }
        else if(!_flag && quantite_soin==0){
            //Ne rien faire
        }
        else{
            setPixmap(QPixmap(":/soin-vide.png"));
            _flag=0;
            quantite_soin = quantite_soin + 1;

        }
        break;
    }
}

void Besoin::reset(){
    _flag=0;
    setPixmap(QPixmap(_show));
}
