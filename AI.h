#include "Maze.cpp"

class AI
{
public:
    vector<pair<pair<int, int>, Direction>> ans;
    virtual void solve() = 0;
    bool getAns;
    Maze m;
    void output();
    AI(Maze maze)
    {
        this->m = maze;
    }
    //ans.push_back(make_pair(make_pair(1,2),UP));
};

void AI::output()
{
    string s[] = {"x", "上", "右", "下", "左"};
    for (auto it : ans)
        cout << "坐标(" << it.first.first << ", " << it.first.second << ") 下一步：" << s[(int)it.second] << endl;
}

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

void Dfs::solve()
{
    getAns = false;
    auto st = m.getStart();
    dfs(st);
}

void Dfs::dfs(pair<int,int> p)
{
    if(p == m.getEnd())
    {
        //output(); 
        getAns = true;
        return;       
    }
    visited[p] = 1;
    auto d = m.getDirections(p.first,p.second);
    for(auto it : d)
    {
        auto next = m.getXY(p,it);
        if(visited[next] == 1)
            continue;
        
        ans.push_back(make_pair(p,it));
        dfs(next);
        if(getAns)
            break;
        //ans.pop_back();
        ans.push_back(make_pair(next,(Direction)(((int)it+1)%4+1)));
        visited[next] = 0;
    }
}

void Bfs::solve()
{
}

void QLearning::solve()
{
}
