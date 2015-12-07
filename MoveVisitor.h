#ifndef MOVEVISITOR_H_INCLUDED
#define MOVEVISITOR_H_INCLUDED
#include "GraphicsVisitor.h"
#include "Graphics.h"

#include <string>

class MoveVisitor : public GraphicsVisitor {
public:
    MoveVisitor(int x,int y);
    void visitSimpleGraphics(SimpleGraphics *sg);
    void visitCompositeGraphics (CompositeGraphics *cg);
    void enter(){};
    void leave(){};
private:

private:
    int x,y;
};

#endif // DESCRIPTIONVISITOR_H_INCLUDED
