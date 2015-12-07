#ifndef DRAWERVISITOR_H
#define DRAWERVISITOR_H
#include "DescriptionVisitor.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Rectangle.h"
#include "GraphicsVisitor.h"
#include "Graphics.h"
#include "Painter.h"
#include "Shape.h"
#include <QWidget>
#include <QGraphicsScene>
#include "Group.h"
#include <stdio.h>
#include <string.h>

class DrawerVisitor : public GraphicsVisitor
{
    public:
        DrawerVisitor(QGraphicsScene* scene, QWidget *widget);
        virtual ~DrawerVisitor();
        void visitSimpleGraphics(SimpleGraphics *sg);
        void visitCompositeGraphics (CompositeGraphics *cg);
        QList<QGraphicsItem *> list;
        QGraphicsItem *parent=NULL;
//        QGraphicsItemGroup *parent=NULL;
    protected:

    private:

        QWidget *widget;
        QGraphicsScene* scene;
        Painter *painter;
        void display(int x, int y, int w, int l, int type, Graphics *g);
        void display(int x, int y, int r,int type, Graphics *g);
        void setting(Painter *item, int type);
};

#endif // DRAWERVISITOR_H
