#include <iostream>
#include "astar.h"
int main() {
    Astar astar;
    Node * startPos = new Node(2,2);
    Node * endPos  = new Node(4,4);
    astar.search(startPos,endPos);
    return 0;
}
