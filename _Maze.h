#ifndef MAZE_H
#define MAZE_H

#include<memory>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Global.h"
#if QT
#include<QString>
#endif

using namespace std;

/**
 * 类型: 地图中的格子
 */
class MazeElem
{
private:
    _MazeElem type;                         //格子类型
public:
    //强化学习所需
    double value;                           //价值(随迭代变化)
    double reward;                          //奖励(固定)
public:
    MazeElem(_MazeElem type = ROAD);
    _MazeElem getType();                    //获取格子类型
    void setType(_MazeElem tp, double val = 0);         //设置格子类型
    void setType(_MazeElem tp, double val, double rew); //设置格子类型

    bool operator==(_MazeElem type);        //重载比较运算符
};

/**
 * 类型: 地图
 */
class Maze
{
public:
    int row;                                //行数
    int col;                                //列数
    pair<int,int> gamer;                    //角色坐标
    pair<int,int> start;                    //入口坐标
    pair<int,int> end;                      //出口坐标
    vector<vector<MazeElem>> game_map;      //地图
    #if QT
    QString
    #else
    string
    #endif 
        MapStytle[4][22];               //地图风格字符串
public:
    Maze(int row, int col);                 //构造函数，同时生成地图
    Maze(){initialMapStytle();}             //构造函数：初始未生成地图
    ~Maze();

    vector<vector<MazeElem>> getMap();       //获取地图
    int getRow();                            //获取地图行数
    int getCol();                            //获取地图列数
    pair<int,int> getStart(){return start;}  //获取入口坐标
    pair<int,int> getEnd(){return end;}      //获取出口坐标

    void genMap();                            //生成随机地图(随机prime算法)，同时设置起点终点坐标
    pair<int,int> genGap(unsigned int _Seed); //生成随机入口和随机出口
    void getWall(int x, int y,vector<pair<pair<int,int>,Direction>> &blocks); //返回坐标相邻的墙体(随机prime算法辅助函数)

    bool walkable(int x,int y);               //判断坐标(x,y)是否可走

    vector<Direction> getDirections(int x, int y);    //返回在当前坐标下一步能走的各个方向
    pair<int,int> getXY(pair<int,int> point, Direction now);  //给出当前坐标和方向，返回下一步坐标
    
    //QT
    void initialMaze(int row,int col);    //初始化地图矩阵
    void initialMapStytle();              //初始化地图风格字符串
    void setCharacterPos();               //设置角色位置
    void setExitPos();                    //设置出口坐标

    //强化学习辅助函数
    void estPoint(int r, int c, double estpay);    //用于在迭代过程中更新预期值
    bool isFixedPoint(int r, int c);               //判断是否为value固定点，即格子value值不可改变

#if debug_global
    void print();            //[测试]:在命令行中打印迷宫
    void printValue();       //[测试]:打印训练的Q表
#endif
};

#endif
