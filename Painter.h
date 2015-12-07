#pragma once
#ifndef PAINTER_H
#define PAINTER_H
#include "Graphics.h"
#include "MoveVisitor.h"
#include <QPainter>
#include <QGraphicsItem>
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
class Painter:public QGraphicsItem
{
    public:
        Painter( int _posx, int _posy, int _width, int _heigh,QWidget *_widget, Graphics *g,QGraphicsScene* scene, int _type);
        Painter( int _posx, int _posy, int _r, QWidget *_widget, bool _cir, Graphics *g,QGraphicsScene* scene, int _type);
        virtual ~Painter();

        QWidget *widget;
        const QRectF *rectptr;
        int posx;
        int posy;
        int width;
        int heigh;
        int r;
        QRectF boundingRect() const;//必須實做的virtual function，但目前用不到
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
        void setColor(int i);
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
        QColor color= Qt::blue;
        int type;
        bool clicked = false;
        int itemID;
};

#endif // PAINTER_H
