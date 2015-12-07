#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "Shape.h"
#include "Rectangle.h"
class Circle : public Shape{
public:
    Circle(int center_x, int center_y, int radius);
    int area();
    Rectangle getBoundingBox();
    std::string describe();
    int get_cx(){return cx;}
    int get_cy(){return cy;}
    int get_r(){return r;}
    void addX(int x){cx+=x;}
    void addY(int y){cy+=y;}
    //int perimeter();
private:
    int cx, cy;
    int r;
};

#endif // CIRCLE_H_INCLUDED
