//
// Created by user on 2020/11/2.
//
#include "astar.h"

#include <iostream>


int Astar::time_zone_of(int x, int y){
    return (y % 2 != 0)?
           ( ((y+1)%4 != 0)? (1+(x+1)%4) : (1+(x+3)%4) ) :
           ( (y%4 == 0)? (4-(x+3)%4) : (4-((x+1)%4)) );
}

Astar :: Astar()
{}

Astar :: ~Astar()
{}

void Astar ::search(Node *startPos, Node *endPos)
{
    ///如果起点坐标小于0 或 超出地图范围
    ///终点地图坐标小于0 或 超出地图范围
    if(startPos->x < 0 || startPos->y > row ||
       startPos->y < 0 || startPos->y > col ||
       endPos->x < 0 || endPos->x > row ||
       endPos->y < 0 || endPos->y >col)
        return ;
    Node * current;
    this->startPos = startPos;
    this->endPos = endPos;
    openList.push_back(startPos);///开启列表中放入起点
    while(openList.size()>0)///循环 只要开启列表中有值
    {
        current = openList[0]; ///将排序后(从小到大)的开启列表第一个节点赋值给当前节点
        ///如果当前节点坐标和终点坐标相同 那么打印地图 打印路径 情况两个列表退出循环
        if(current->x == endPos->x && current->y == endPos->y)
        {
            std ::cout << "find the path" << std::endl;
            printMap();
            printPath(current);
            openList.clear();
            closeList.clear();
            break;
        }
        ///如果不是终点坐标 把当前点传递给NextStep函数处理
        NextStep(current);
        ///将当前节点加入关闭列表中
        closeList.push_back(current);
        ///将上一个加入关闭列表中的节点从开启列表中删除
        openList.erase(openList.begin());
        ///将开启列表从小到大排序
        sort(openList.begin(),openList.end(),compare);
    }
}
///对传入的当前节点 进行下一步处理 检查它周围的四个点是否能够通行
void Astar ::NextStep(Node *current)
{
    checkPoint(current->x-1 , current->y , current,wayCost);//左
    checkPoint(current->x+1 , current->y , current,wayCost);//右
    checkPoint(current->x , current->y+1 , current,wayCost);//下
    checkPoint(current->x , current->y-1 , current,wayCost);//上
}
///具体检查下一个节点的函数
void Astar ::checkPoint(int x,int y, Node *father,int g)
{
    int x1 = father->x;
    int y1 = father->y;
    ///越界
    if(x < 0 || x > row || y < 0 || y > col)
        return;
    ///时钟约束下的路径
    if(unWalk(x1,y1,x,y)){
        return;
    }
    ///遍历关闭列表 如果点存在直接返回
    if(isContains(&closeList,x,y) != -1)
        return;
    int index;
    ///遍历开启列表 如果点存在开启列表中,把点赋值给index 进行下一步对f值大小判断
    if((index = isContains(&openList,x,y))!=-1)
    {
        Node* point = openList[index];
        ///如果openList中点的g值大于其父节点+一格子的移动代价
        if(point->g > father->g +g)
        {
            ///father参数此时传入的值是current结点 因此把当前节点视为下一个节点的父节点
            point->father = father;
            ///当前节点的g值 = 父节点的g值 + 移动一格的代价
            point->g = father->g+g;
            ///计算当前节点的f值
            point->f = point->g + point->h;
        }
    }
    else
    ///如果点不在开启列表中 堆区开辟一块新的内存
    {
        Node*point = new Node(x,y,father);
        ///计算该点的F值
        countGHF(point,endPos,g);
        ///把该点放入开启列表中
        openList.push_back(point);
    }
}
///遍历整个列表 查找点是否存在列表中
int Astar::isContains(std::vector<Node *> *Nodelist, int x, int y)
{
    for(int i = 0;i < Nodelist->size();i++)
    {
        if(Nodelist->at(i)->x == x && Nodelist->at(i)->y == y)
        {
            return i;
        }
    }
    return -1;
}

void Astar::countGHF(Node *sNode, Node *eNode, int g)
{
    ///计算h值 也就是曼哈顿街区距离 两点之间坐标的绝对值相减的和 再乘上移动代价
    int h = (abs(sNode->x - eNode->x)+abs(sNode->y - eNode->y))*wayCost;
    ///当前节点的g值 = 节点父节点的g值 + g值
    int currentg = sNode->father->g + g;
    int f = currentg + h;//计算f值
    sNode->f = f;
    sNode->h = h;
    sNode->g = currentg;
}

bool Astar ::compare(Node *n1, Node *n2)
{
    return n1->f < n2->f;
}

bool Astar::unWalk(int &x1, int &y1, int &x, int &y)
{
   /* int x = node.x;
    int y = node.y;
    if(      (map[x+1][y]-map[x][y]==1)
          || (map[x-1][y]-map[x][y]==1)
          || (map[x][y+1]-map[x][y]==1)
          || (map[x][y-1]-map[x][y]==1)
          || (map[x+1][y]-map[x][y]==-3)
          || (map[x-1][y]-map[x][y]==-3)
          || (map[x][y+1]-map[x][y]==-3)
          || (map[x][y-1]-map[x][y]==-3)
            )
    {
        return false;
    }
    else
        return true;
    */

    if( time_zone_of(x1,y1) == 1 && time_zone_of(x,y) == 4 ) return false;
    if( time_zone_of(x1,y1) == 4 && time_zone_of(x,y) == 1 ) return true;
    return ( time_zone_of(x1,y1) < time_zone_of(x,y) );
}

void Astar::printPath(Node *current)
{
    if (current->father != NULL)
        printPath(current->father);
    std::cout <<'('<< current->x <<',' << current->y << ')' << std::endl;
}

void Astar::printMap()
{
    for(int i = 0; i< row;i++)
    {
        {
           for (int j = 0; j < col; j++)
                std::cout << " " << time_zone_of(i ,j);
        }
        std::cout << std::endl;
    }
}