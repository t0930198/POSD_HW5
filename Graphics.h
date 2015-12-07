#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include "shape.h"
#include <vector>
class Rectangle;
class GraphicsVisitor;

class Graphics{
public:
    virtual ~Graphics();
    virtual Rectangle getBoundingBox();
    virtual void add(Graphics *g);
    virtual void accept(GraphicsVisitor & av);
    virtual Shape* shape()=0;
    void setID(int id){itemID=id;}
    int getID(){return itemID;}
    virtual std::vector<Graphics *> getObj(){}
protected:
    Graphics();
private:
    int itemID;
};

#endif // GRAPHICS_H_INCLUDED
