#ifndef COMPOSITEGRAPHICS_H_INCLUDED
#define COMPOSITEGRAPHICS_H_INCLUDED

#include "Graphics.h"
#include <vector>
#include "GraphicsVisitor.h"

class CompositeGraphics : public Graphics {
public:
    CompositeGraphics();
    void add (Graphics *g);
    Rectangle getBoundingBox();
    void accept(GraphicsVisitor & av);
    Shape * shape(){};
    std::vector<Graphics *> getObj(){return g_obj;}
private:
    std::vector<Graphics *> g_obj;
};

#endif // COMPOSITEGRAPHICS_H_INCLUDED
