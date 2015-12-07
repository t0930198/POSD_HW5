#ifndef GRAPHICSFACTORY_H_INCLUDED
#define GRAPHICSFACTORY_H_INCLUDED

#include "Graphics.h"
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class GraphicsFactory {
public:
    vector<Graphics *> buildGraphicsFromFile(const char * fileName); /*implement the pseudo code */
    string fileContentsAsString(const char * fileName); /* implement line 1 of pseudo code */
    Graphics * extractGraphicsFromOneLine(string & contents, int & level, int &itemID); /*implement line 3 */
    bool compose (); /* implement lines 5, 6 as well as line 8 */
    int itemID=0;
public:

    stack<pair<int, Graphics *> > pda;
};


#endif // GRAPHICSFACTORY_H_INCLUDED
