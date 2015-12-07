#include "Group.h"

Group::Group(QGraphicsItem * parent)
{

}

Group::Group(Graphics *_g, QGraphicsScene* _scene, QGraphicsItem * parent)
{
     this->setFlag(QGraphicsItem::ItemIsSelectable, true);
     itemID = _g->getID();
     this->setData(0,QVariant(itemID));
     posx = _g->getBoundingBox().llx();
     posy = _g->getBoundingBox().lly();
     width = _g->getBoundingBox().urx()-_g->getBoundingBox().llx();
     heigh = _g->getBoundingBox().ury()-_g->getBoundingBox().lly();
}

Group::~Group()
{
    //dtor
}


QRectF Group::boundingRect() const
{
    return QRectF(posx,posy,width,heigh);
}



void Group::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    //cout<<"paint";

    QPen pen(this->color);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawRect(QRectF(posx, posy, width, heigh));


}

void Group::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Group::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Group::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);// tell the base class we are handling this event
    cout<<"x:"<<boundingRect().x()<<" y:"<<boundingRect().y()<<" w:"<<boundingRect().width()<<" h:"<<boundingRect().height()<<endl;

    QPointF qp = event->pos() ;

    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<endl;
}

void Group::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    // allow the user to drag the box, capture the starting position on mouse-down
    event->setAccepted(true);
    QPointF qp = event->pos() ;
    prex = qp.x();
    prey = qp.y();
    offsetx = qp.x()-posx;
    offsety = qp.y()-posy;
    this->setSelected(true);
    qDebug()<<this->isSelected();
    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<" pos:("<<qp.x()-offsetx<<","<<qp.y()-offsety<<")"<<endl;
}

void Group::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    // user have moved the mouse, move the location of the box
    QPointF qp = event->pos() ;
    posx = qp.x()-offsetx;
    posy = qp.y()-offsety;
//    if(type==0){
//        posx = qp.x()-offsetx;
//        posy = qp.y()-offsety;
//    } else {
//
//    }
    scene->update();
    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<" pos:("<<qp.x()-offsetx<<","<<qp.y()-offsety<<")"<<endl;
}

void Group::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    // return the box color to black when the mouse is no longer hovering
//    _outterborderColor = Qt::black;
//    this->update(0,0,_width,_height);
}

void Group::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    // draw the box in red if the mouse is hovering over it
//    _outterborderColor = Qt::red;
//    this->update(0,0,_width,_height);
}
