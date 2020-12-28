#include <iostream>
#include "astar.h"
int main() {
    Astar astar;
    Node * startPos = new Node(7,9);
    Node * endPos  = new Node(1,3);
    astar.search(startPos,endPos);
    return 0;
}
