#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "Shape.h"

class Square : public Shape {
public:
    Square(int ll_x, int ll_y, int length);
    int area();
    Rectangle getBoundingBox();
    std::string describe();
    void addX(int _x){x+=_x;}
    void addY(int _y){y+=_y;}
private:
    int x, y;
    int l;

};


#endif // SQUARE_H_INCLUDED
