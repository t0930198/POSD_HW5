#include "Painter.h"

Painter::Painter(int _posx, int _posy, int _width, int _heigh,QWidget *_widget, Graphics *_g,QGraphicsScene* _scene, int _type)
{
    //ctor
     posx = _posx;
     posy = _posy;
     width = _width;
     heigh = _heigh;
     widget = _widget;
     cir = false;
     r=0;
     g=_g;
     scene = _scene;
     type=_type;
     this->setFlag(QGraphicsItem::ItemIsMovable,true);
     this->setFlag(QGraphicsItem::ItemIsSelectable, true);
     itemID = _g->getID();
     this->setData(0,QVariant(itemID));
}

Painter::Painter(int _posx, int _posy, int _r, QWidget *_widget, bool _cir, Graphics *_g,QGraphicsScene* _scene, int _type)
{

    //ctor
     posx = _posx;
     posy = _posy;
     r = _r;
     width = 2*_r;
     heigh = 2*_r;
     cir = _cir;
     widget = _widget;
     g=_g;
     scene = _scene;
     type=_type;
     this->setFlag(QGraphicsItem::ItemIsMovable,true);
     this->setFlag(QGraphicsItem::ItemIsSelectable, true);
     itemID = _g->getID();
     this->setData(0,QVariant(itemID));
}

Painter::~Painter()
{
    //dtor
}


QRectF Painter::boundingRect() const
{
    if(!cir)
        return QRectF(posx,posy,width,heigh);
    else
        return QRectF(posx-r,posy-r,width,heigh);
}



void Painter::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    //cout<<"paint";

    QPen pen(this->color);
    pen.setWidth(3);
    painter->setPen(pen);
    if(!cir){

        painter->drawRect(QRectF(posx, posy, width, heigh));
//        QPen pen2(Qt::black);
//        pen2.setWidth(1);
//        painter->setPen(pen2);
//        painter->drawRoundedRect(QRectF(posx, posy, width, heigh),0,0);
    }else
    {
        painter->drawEllipse(QPointF(posx,posy), r, r);
//        QPen pen2(Qt::black);
//        pen2.setWidth(1);
//        painter->setPen(pen2);
//        painter->drawRoundedRect(QRectF(posx-r, posy-r, width, heigh),0,0);
    }


}
//i->0 blue i->1 green
void Painter::setColor(int i){
    if(i==0)
        this->color=Qt::blue;
    else
        this->color=Qt::green;
}

void Painter::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Painter::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Painter::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);// tell the base class we are handling this event
    cout<<"x:"<<boundingRect().x()<<" y:"<<boundingRect().y()<<" w:"<<boundingRect().width()<<" h:"<<boundingRect().height()<<endl;
    if(this->childItems().size()>0){
        for(auto e:this->childItems()){
            this->scene->sendEvent(e,event);
        }
    }
    QPointF qp = event->pos() ;
    if(type==0){
        g->shape()->addX(qp.x()-prex);
        g->shape()->addY(qp.y()-prey);
    }
    if(type==0){
        if(this->isSelected())
        cout<<g->shape()->describe()<<" selected"<<endl;
    }
    else{
        cout<<"comp"<<endl;
    }

    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<endl;
}

void Painter::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    // allow the user to drag the box, capture the starting position on mouse-down
    event->setAccepted(true);
    if(this->childItems().size()>0){
        for(auto e:this->childItems()){
            this->scene->sendEvent(e,event);
        }
    }
    QPointF qp = event->pos() ;
    prex = qp.x();
    prey = qp.y();
    offsetx = qp.x()-posx;
    offsety = qp.y()-posy;
    this->setSelected(!clicked);
    clicked = !clicked;
    if(clicked){
        this->color=Qt::red;
    }
    else{
        if(type==0)
            this->color=Qt::blue;
        else this->color=Qt::green;
    }
    qDebug()<<this->isSelected();

    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<" pos:("<<qp.x()-offsetx<<","<<qp.y()-offsety<<")"<<endl;
}

void Painter::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    // user have moved the mouse, move the location of the box
    QPointF qp = event->pos() ;
    posx = qp.x()-offsetx;
    posy = qp.y()-offsety;
    if(this->childItems().size()>0){
        for(auto e:this->childItems()){
            this->scene->sendEvent(e,event);
        }
    }
    scene->update();
    cout<<"press x:"<<qp.x()<<"y:"<<qp.y()<<" pos:("<<qp.x()-offsetx<<","<<qp.y()-offsety<<")"<<endl;
}

void Painter::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    // return the box color to black when the mouse is no longer hovering
//    _outterborderColor = Qt::black;
//    this->update(0,0,_width,_height);
}

void Painter::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    // draw the box in red if the mouse is hovering over it
//    _outterborderColor = Qt::red;
//    this->update(0,0,_width,_height);
}
