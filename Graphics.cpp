#include "Graphics.h"
#include "Rectangle.h"
#include <string>
#include "AreaVisitor.h"
#include <iostream>
using namespace std;
Rectangle Graphics:: getBoundingBox() {return Rectangle(0,0,0,0);}
void Graphics::add(Graphics *g) {throw std::string("Cannot add child");}
void Graphics::accept(GraphicsVisitor & av) {}
Graphics::Graphics(){}
Graphics::~Graphics(){}



