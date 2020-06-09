#include "AI.h"
#include<deque>

void AI::output()
{
    string s[] = {"x", "上", "右", "下", "左"};
    for (auto it : ans)
        cout << "坐标(" << it.first.first << ", " << it.first.second << ") 下一步：" << s[(int)it.second] << endl;
}

void Dfs::solve()
{
    visited.clear();
    getAns = false;
    auto st = m.getStart();
    dfs(st);
}

void Dfs::dfs(pair<int, int> p)
{
    if (p == m.getEnd())
    {
        //output();
        getAns = true;
        return;
    }
    visited[p] = 1;
    auto d = m.getDirections(p.first, p.second);
    for (auto it : d)
    {
        auto next = m.getXY(p, it);
        if (visited[next] == 1)
            continue;

        ans.push_back(make_pair(p, it));
        dfs(next);
        if (getAns)
            break;
        if(bestPath == true)
            ans.pop_back();
        else
            ans.push_back(make_pair(next, (Direction)(((int)it + 1) % 4 + 1)));
        visited[next] = 0;
    }
}

#define debug_bfs 0
void Bfs::solve()
{
    Maze tmp_m = m;
    AI *tmp;
    pair<int,int> pre;

    visited.clear();
    deque<pair<int, int>> q;
    q.push_back(m.getStart());         //起点加入队列

    while (!q.empty())
    {
        pair<int, int> p = q.front();  //取出队首
        q.pop_front();

        /*需要从上一位置来到当前位置*/
        tmp_m.start = pre;
        tmp_m.end = p;
        tmp = new Dfs(tmp_m,true);
        tmp->solve();
        ans.insert(ans.end(),tmp->ans.begin(),tmp->ans.end());

        #if debug_bfs
        cout<<endl<<"<dfs>"<<endl;
        string s[] = {"x", "上", "右", "下", "左"};
        for(auto it : tmp->ans)
            cout<<it.first.first<<","<<it.first.second<<"  "<<s[it.second]<<endl;
        cout<<endl;
        #endif

        visited[p] = 1;
        auto d = m.getDirections(p.first, p.second);  //获得能访问的方向

        #if debug_bfs
        cout<<d.size()<<" "<<s[d[0]]<<" "<<p.first<<", "<<p.second<<endl;
        #endif

        for (auto it : d)
        {
            pair<int, int> next = m.getXY(p, it);     //获得下一步坐标
            if(visited[next] == 1)                    //避免往回走
                continue;
            ans.push_back(make_pair(p,it));           //更新寻路结果

            #if debug_bfs
            string s[] = {"x", "上", "右", "下", "左"};
            cout<<p.first<<","<<p.second<<"  "<<s[it]<<endl;
            #endif

            if (next == m.getEnd())
            {
                #if debug_bfs
                cout<<ans.size()<<endl;
                #endif

                return;
            }
            Direction reverse = (Direction)(((int)it + 1) % 4 + 1);  //反方向
            ans.push_back(make_pair(next, reverse));        //更新寻路结果，返回上一步

            auto next_d = m.getDirections(next.first,next.second);
            if(next_d.size() == 1 && next_d[0] == reverse)
                ;
            else q.push_back(next);                        //将下一步坐标放到队尾
        }
        #if debug_bfs
        cout<<endl;
        #endif

        pre = p;
    }
}

void QLearning::solve()
{
}

#if debug_AI_main
int main()
{
    Maze maze(10,10);
    maze.print();
    
    AI *ai = new Dfs(maze);
    ai->solve();
    ai->output();

    return 0;
}
#endif
