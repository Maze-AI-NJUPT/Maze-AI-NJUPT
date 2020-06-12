#include "_Maze.h"
#include<map>
class AI
{
public:
    vector<pair<pair<int, int>, Direction>> ans;
    Maze m;

    virtual void solve() = 0;       //寻路算法
    void output();                  //命令行输出寻路结果
    AI(Maze maze){this->m = maze; ans.clear();}
};

class Dfs : public AI
{
private:
    map<pair<int, int>, int> visited;
    bool bestPath;
    bool getAns;                 //是否到达终点
public:
    Dfs(Maze maze,bool bestPath = false) : AI(maze) {this->bestPath = bestPath; getAns=false; visited.clear();}
    void solve();
    void dfs(pair<int, int> p);
};

class Bfs : public AI
{
private:
    map<pair<int, int>, int> visited;

public:
    Bfs(Maze maze) : AI(maze) {visited.clear();}
    void solve();
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
    QLearning(Maze maze, int times = TIMES);
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


