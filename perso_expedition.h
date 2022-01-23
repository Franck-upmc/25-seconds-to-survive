#ifndef PERSO_EXPEDITION_H
#define PERSO_EXPEDITION_H

#include <QGraphicsPixmapItem>
#include "custompixmapitem.h"
#include <QGraphicsSceneMouseEvent>

class Perso_expedition : public QGraphicsPixmapItem
{
public:
    Perso_expedition(e_Type type, QGraphicsItem *parent=nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void reset();
    void image_vide();
    void image_pleine();
    int get_pick(){return _pick;}
    int get_p(){return p;}
    int get_push(){return _push;}
    e_Type get_type(){return _type;}
private:
    static int p;
    int _push=0;
    int _pick=0;
    QString _img;
    e_Type _type;
};

#endif // PERSO_EXPEDITION_H
