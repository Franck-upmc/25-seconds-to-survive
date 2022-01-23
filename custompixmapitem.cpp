#include "custompixmapitem.h"

int CustomPixmapItem::cpt=0;
int CustomPixmapItem::inv=1;

CustomPixmapItem::CustomPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent):
    QGraphicsPixmapItem(pixmap,parent){}


CustomPixmapItem::CustomPixmapItem(e_Type type,QGraphicsItem *parent):
    QGraphicsPixmapItem(parent){
    _type=type;
    switch(type){
        case MERE:
            setPixmap(QPixmap(":/mere_tete.png"));
            _image=":/mere.png";
            break;
        case EAU:
            setPixmap(QPixmap(":/bouteille-eau-bunker.png"));
            _image=":/bouteille-eau-bunker.png";
            break;
        case NOURRITURE:
            setPixmap(QPixmap(":/bouffe-bunker.png"));
            _image=":/bouffe-bunker.png";
            break;
        case LAMPE_TORCHE:
            setPixmap(QPixmap(":/lampe-bunker.png"));
            _image=":/lampe-bunker.png";
            break;
        case CORDE:
            setPixmap((QPixmap(":/corde-bunker.png")).scaled(50,50));
            _image=":/corde-bunker.png";
            break;
        case RADIO:
            setPixmap((QPixmap(":/radio-bunker.png")).scaled(50,50));
            _image=":/radio-bunker.png";
            break;
        case HACHE:
            setPixmap((QPixmap(":/hache-bunker.png")).scaled(50,50));
            _image=":/hache-bunker.png";
            break;
        case FUSIL:
            setPixmap((QPixmap(":/fusil-bunker.png")).scaled(50,50));
            _image=":/fusil-bunker.png";
            break;
        case CALENDRIER:
            setPixmap((QPixmap(":/calendrier-bunker.png")).scaled(50,50));
            _image=":/calendrier-bunker.png";
            break;
        case LIVRE:
            setPixmap((QPixmap(":/livre_ferme.png")).scaled(50,50));
            _image=":/livre_ferme.png";
            break;
        case MASQUE_GAZ:
            setPixmap((QPixmap(":/masque_gaz.png")).scaled(50,50));
            _image=":/cpp_image.png";
            break;
        case HORLOGE:
            setPixmap((QPixmap(":/horloge-bunker.png")).scaled(50,50));
            _image=":/horloge-bunker.png";
            break;
        case JEUX_SOCIETE:
            setPixmap((QPixmap(":/jeux-bunker.png")).scaled(50,50));
            _image=":/jeux-bunker.png";
            break;
        case PERE:
            setPixmap(QPixmap(":/pere_tete.png"));
            _image=":/pere.png";
            break;
        case FILS:
            setPixmap(QPixmap(":/fils_tete.png"));
            _image=":/fils.png";
            break;
        case FILLE:
            setPixmap(QPixmap(":/fille_tete.png"));
            _image=":/fille.png";
            break;
        case KIT_SOIN:
            setPixmap(QPixmap(":/soin-bunker.png"));
            _image=":/soin-bunker.png";
            break;
        default:
            qDebug()<<"Problème";
            break;
    }
}

void CustomPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    if(cpt<2){
        setPos(QPointF(20 + inv*70,330));
        in_inventaire=true;
        inv++;
        cpt++;
     }
}

