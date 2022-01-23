#ifndef BESOIN_EXPEDITION_H
#define BESOIN_EXPEDITION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "Objet.hh"
#include <iostream>

class Besoin_expedition : public QGraphicsPixmapItem
{
public:
    Besoin_expedition(e_Type type, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void reset();
    e_Type get_type(){return _type;}
    int get_pick(){return _pick;}
    int get_p(){return p;}
    int get_push(){return _push;}
private:
    void image_pleine();
    void image_vide();
    static int p;
    int _pick=0;
    int _push=0;
    e_Type _type;
};

#endif // BESOIN_EXPEDITION_H
