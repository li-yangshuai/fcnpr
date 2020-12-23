//
// Created by user on 2020/11/2.
//

#ifndef ASTAR_H
#define ASTAR_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef struct Node
{
    int x,y;
    int g;
    int h;
    int f;
    Node* father;
    Node(int x,int y)
    {
        this->x = x;
        this->y = y;
        this->g = 0;
        this->h = 0;
        this->f = 0;
        this->father = NULL;
    }
    Node(int x,int y,Node* father)
    {
        this->x = x;
        this->y = y;
        this->g = 0;
        this->h = 0;
        this->f = 0;
        this->father = father;
    }
}Node;

class Astar
{
public:
    Astar();
    ~Astar();

    void search(Node* startPos,Node* endPos);//搜索路径

    void checkPoint(int x, int y, Node * father,int g);//检查周围结点

    void NextStep(Node * currentPoint);//下一个合适的结点

    int isContains(std::vector<Node*>* Nodelist,int x,int y);

    void countGHF(Node* sNode,Node * eNode,int g);

    static bool compare(Node * n1,Node *n2);

    bool unWalk(int &x1, int &y1, int &x, int &y);

    int time_zone_of(int x, int y);


    void printPath(Node* current);

    void printMap();

    std :: vector <Node*> openList;
    std :: vector <Node*> closeList;

    Node * startPos;
    Node * endPos;

    static const int wayCost = 10;
    static const int row = 10;
    static const int col = 10;

};

#endif

