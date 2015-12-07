#pragma once
#ifndef GROUP_H
#define GROUP_H
#include "Graphics.h"
#include <QPainter>
#include "Rectangle.h"
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QAction>
#include <QStaticText>
#include "qwidget.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QColor>
#include <QPen>
#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QFocusEvent>
#include <QDebug>
using namespace std;
class Group:public QGraphicsItemGroup
{
    public:
        Group(QGraphicsItem * parent = 0);
        Group(Graphics *_g, QGraphicsScene* _scene, QGraphicsItem * parent = 0);

        virtual ~Group();

        QWidget *widget;
        const QRectF *rectptr;
        int posx;
        int posy;
        int width;
        int heigh;
        int r;
        QRectF boundingRect() const;//必須實做的virtual function，但目前用不到
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
        int getID(){return itemID;}
        void setID(int id){itemID=id;}

    protected:
        virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
        virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events
        virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );///< re-implemented to capture events
        virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);///< re-implemented to capture events
        virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );///< re-implemented to capture events
        virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);///< re-implemented to capture events
        virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );///< re-implemented to capture events

    private:
        qreal prex,prey,postx,posty,offsetx,offsety;
        Graphics *g;
        bool cir;
        QGraphicsScene* scene;
        QColor color= Qt::green;
        int type;
        int itemID;
};

#endif // PAINTER_H
