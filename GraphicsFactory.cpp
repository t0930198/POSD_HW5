#include "GraphicsFactory.h"

#include <vector>
#include <fstream>
#include <sstream>
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "util.h"

bool GraphicsFactory::compose () {
    vector<Graphics *> temp;
    int level=(pda.top().first);
    if(level==0){
        return false;
    }
    for (; (pda.top().first) == level; pda.pop()){

        temp.push_back((pda.top().second));
        }
    cout<<"....";
    if ((pda.top().first) == level-1) {
        vector<Graphics *>::reverse_iterator it = temp.rbegin();
        for (; it != temp.rend(); ++it) {
            (pda.top().second)->add(*it);
        }
    }
    return true;
}

string GraphicsFactory::fileContentsAsString(const char * fileName) {
	ifstream ifs(fileName);
	if (!ifs)
        throw "Problem opening file";

    string contents("");
    string s;
    while (getline(ifs,s))
    {
        contents.append(s);
        contents.append(string("\n"));
    }

	if (ifs.is_open())
		ifs.close();
    return contents;
}

Graphics * GraphicsFactory::extractGraphicsFromOneLine(std::string & contents, int & level, int &itemID) {
    std::size_t pos = contents.find_first_not_of(space);
    level = pos/2;
    Graphics * gr =0;

    std::size_t found = contents.find("Comp ", pos);
    if (found==pos)
        gr = new CompositeGraphics;
    found = contents.find("C(", pos);
    if (found==pos) {
        std::string s(contents.substr(pos+2));
        std::stringstream ifs(s);
        int cx, cy, r;
        char c;
        //     cx    ,    cy    ,    r    )
        ifs >> cx >> c >> cy >> c >> r >> c;
        gr = new SimpleGraphics(new Circle(cx,cy,r));
    }
    found = contents.find("S(", pos);
    if (found==pos) {
        std::string s(contents.substr(pos+2));
        std::stringstream ifs(s);
        int llx, lly, length;
        char c;
        //     llx    ,    lly    ,    length    )
        ifs >> llx >> c >> lly >> c >> length >> c;
        gr = new SimpleGraphics(new Square(llx, lly,length));
    }

    found = contents.find("R(", pos);
    if (found==pos) {
        std::string s(contents.substr(pos+2));
        std::stringstream ifs(s);
        int llx, lly, length, width ;
        char c;
        //     llx    ,    lly    ,    length    ,    width    )
        ifs >> llx >> c >> lly >> c >> length >> c >> width >> c;
        gr = new SimpleGraphics(new Rectangle(llx, lly,length,width));
    }

    pos=contents.find_first_of(newline, 0);
    contents = contents.substr(pos+1);
    gr->setID(itemID);
    itemID++;
    if (gr)
        return gr;
    else
        throw std::string("undefined graphics");
}

vector<Graphics *> GraphicsFactory::buildGraphicsFromFile(const char * fileName) {
    vector<Graphics *> gs;
    Graphics * gr = 0;
    int indent_previous, indent_actual;
    std::string contents = fileContentsAsString(fileName);
    Graphics * top = extractGraphicsFromOneLine(contents, indent_actual, itemID);
    if (indent_actual != 0)
        throw std::string("Graphics format error");
    else {
        pda.push(std::make_pair(indent_actual,top));
    }
    while (!contents.empty()) {
        indent_previous = indent_actual;
        Graphics * t = extractGraphicsFromOneLine(contents, indent_actual, itemID);
        if (indent_actual < indent_previous)
            compose();

        pda.push(make_pair(indent_actual,t));
    }
    if (contents.empty()) {
        while (pda.size() > 1){
            if(!compose())
                break;
        }
    }
    while(!pda.empty()){
        gr = (pda.top().second);
        pda.pop();
        gs.push_back(gr);
    }
    return gs;
}
