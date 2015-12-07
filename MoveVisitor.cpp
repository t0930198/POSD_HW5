#include "MoveVisitor.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Rectangle.h"

MoveVisitor::MoveVisitor(int _x, int _y){
    x=_x;
    y=_y;
}
void MoveVisitor::visitSimpleGraphics(SimpleGraphics *sg) {
    sg->shape()->addX(x);
    sg->shape()->addY(y);
}
void MoveVisitor::visitCompositeGraphics (CompositeGraphics *cg) {

}

