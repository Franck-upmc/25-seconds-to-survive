#ifndef BESOIN_H
#define BESOIN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Besoin : public QGraphicsPixmapItem
{
public:
    Besoin(const QPixmap &pixmap, int t=0, QGraphicsItem *parent = nullptr);
    int get_flag(){return _flag;}
    void set_flag(int f){_flag=f;}
    void reset();
    float get_quantite_eau(){return quantite_eau;}
    void set_quantite_eau(float q){quantite_eau=q;}
    float get_quantite_bouffe(){return quantite_bouffe;}
    void set_quantite_bouffe(float q){quantite_bouffe=q;}
    int get_quantite_soin(){return quantite_soin;}
    void set_quantite_soin(int q){quantite_soin=q;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    static float quantite_eau;
    static float quantite_bouffe;
    static int quantite_soin;
    int _flag=0;
    int _t;
    QString _show;
};

#endif // BESOIN_H
