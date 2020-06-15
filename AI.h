#include "_Maze.h"
#include<map>
class AI
{
public:
    vector<pair<pair<int, int>, Direction>> ans;
    Maze m;
    int option;         // 0:AI操作版本  1:寻路路径版本  2:最佳路径版本

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
    map<pair<int, int>, int> visited;

    bool getAns;                 //是否到达终点
public:
    Dfs(Maze maze, int option = 0) : AI(maze,option) {
        getAns=false;
        visited.clear();
    }
    void solve();
    void dfs(pair<int, int> p);
};

class Bfs : public AI
{
private:
    map<pair<int, int>, int> visited;
    vector<vector<Direction>> decision;
    bool simplePath;            //是否单纯的BFS，不保存从一个结点到另一个结点的过程
public:
    Bfs(Maze maze, int option = 0) : AI(maze,option) {
        this->simplePath=simplePath;
        decision.resize(m.row);
        for(int i=0;i<m.row;i++)
            decision[i].resize(m.col);
        visited.clear();
    }
    void solve();
private:
    void getBestPath();
};

class QLearning : public AI
{
private:
    vector<vector<Direction>> decision;
    map<pair<int, int>, int> visited;
    unsigned _cSeq = 0;
public:
    int times;      //训练次数
public:
    QLearning(Maze maze, int times = TIMES, int option = 0);
    ~QLearning() {
        decision.clear();
        /*for (int i = 0; i < m.getRow(); i++)
            delete[] decision[i];
        delete[] decision;*/
    }
    void solve();
#if debug_global
    void printDirection();
#endif
private:
    Direction QLearningDecision(int r, int c);
    void getResult();
};


