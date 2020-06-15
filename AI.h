#include "_Maze.h"
#include<map>
class AI
{
public:
    vector<pair<pair<int, int>, Direction>> ans;    //寻路结果
    Maze m;             //地图
    int option;         // 0->AI操作版本  1->寻路路径版本  2->最佳路径版本

    AI(Maze maze, int option = 0){
        this->m = maze;
        this->option = option;
        ans.clear();
    }
    virtual void solve() = 0;     //寻路算法
    void output();                //命令行输出寻路结果
};

class Dfs : public AI
{
private:
    map<pair<int, int>, int> visited;//标记是否已经访问过的矩阵
    bool getAns;                     //是否到达终点
public:
    Dfs(Maze maze, int option = 0) : AI(maze,option) {
        getAns=false;
        visited.clear();
    }
    void solve();                   //寻路算法入口
    void dfs(pair<int, int> p);     //dfs
};

class Bfs : public AI
{
private:
    map<pair<int, int>, int> visited;  //标记是否已经访问过的矩阵
    vector<vector<Direction>> decision;//保存每个坐标将要走的下一个方向(逆向:从终点到起点)
    bool simplePath;                   //是否单纯的BFS，不保存从一个结点到另一个结点的过程
public:
    Bfs(Maze maze, int option = 0) : AI(maze,option) {
        this->simplePath=simplePath;
        decision.resize(m.row);
        for(int i=0;i<m.row;i++)
            decision[i].resize(m.col);
        visited.clear();
    }
    void solve();                     //寻路算法入口
private:
    void getBestPath();               //不保存寻路过程的结果
};

class QLearning : public AI
{
private:
    vector<vector<Direction>> decision; //标记是否已经访问过的矩阵
    map<pair<int, int>, int> visited;   //保存每个坐标将要走的下一个方向
    unsigned _cSeq = 0;                 //计数
public:
    int times;                          //训练次数
public:
    QLearning(Maze maze, int times = TIMES, int option = 0);
    ~QLearning() {
        decision.clear();
    }
    void solve();                       //寻路算法入口
#if debug_global
    void printDirection();              //打印决策矩阵
#endif
private:
    Direction QLearningDecision(int r, int c); //在坐标(r,c)进行一次QLearning决策
    void getResult();                          //获取寻路结果
};


