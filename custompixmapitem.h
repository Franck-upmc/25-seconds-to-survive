#ifndef CUSTOMPIXMAPITEM_H
#define CUSTOMPIXMAPITEM_H

#include "Objet.hh"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

class CustomPixmapItem : public QGraphicsPixmapItem
{
public:
    CustomPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    CustomPixmapItem(e_Type type=NOURRITURE,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    e_Type get_type(){return _type;}
    void set_cpt(int c){cpt=c;}
    int get_cpt(){return cpt;}
    bool get_in_inventaire(){return in_inventaire;}
    std::string get_image(){return _image;}


private:
    static int cpt;
    static int inv;
    std::string _image;
    bool in_inventaire=false;
    e_Type _type;
};

#endif // CUSTOMPIXMAPITEM_H
