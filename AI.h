#include "_Maze.h"
#include<map>
class AI
{
public:
    vector<pair<pair<int, int>, Direction>> ans;
    virtual void solve() = 0;
    bool getAns;
    Maze m;
    void output();
    AI (){}
    AI(Maze maze)
    {
        this->m = maze;
    }
    //ans.push_back(make_pair(make_pair(1,2),UP));
};


class Dfs : public AI
{
private:
    map<pair<int, int>, int> visited;

public:
    Dfs(Maze maze) : AI(maze){}
    void solve();
    void dfs(pair<int,int> p);
};

class Bfs : public AI
{
public:
    Bfs(Maze maze) : AI(maze){}
    void solve();
};

class QLearning : public AI
{
public:
    QLearning(Maze maze) : AI(maze){}
    void solve();
};


