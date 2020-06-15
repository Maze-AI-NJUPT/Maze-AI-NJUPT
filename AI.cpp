#include "AI.h"
#include<deque>

void AI::output()
{
    string s[] = {"x", "Up", "Right", "Down", "Left"};
    for (auto it : ans)
        cout << "(" << it.first.first << ", " << it.first.second << ") next: " << s[(int)it.second] << endl;
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
    visited.clear();

    Maze tmp_m(m);
    AI *tmp;
    pair<int,int> pre;

    deque<pair<int, int>> q;
    q.push_back(m.getStart());         //起点加入队列

    while (!q.empty())
    {
        pair<int, int> p = q.front();  //取出队首
        q.pop_front();

        /*需要从上一位置来到当前位置*/
        if(!simplePath)
        {
            tmp_m.start = pre;
            tmp_m.end = p;
            tmp = new Dfs(tmp_m,true);
            tmp->solve();
            ans.insert(ans.end(),tmp->ans.begin(),tmp->ans.end());
        }

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
QLearning::QLearning(Maze maze, int times): AI(maze) {
    srand(static_cast<unsigned>(time(NULL)));
    visited.clear();
    this->times = m.row*2+5;
    /*
    decision = new Direction * [m.row];
    for(int i=0;i<m.row;i++)
    {
        decision[i] = new Direction[m.col];
        //memset(decision[i],0,sizeof(decision[i]));
        for(int j=0;j<m.col;j++)
            decision[i][j] = ERR;
    }*/
    decision.resize(m.row);
    for(int i=0;i<m.row;i++)
        decision[i].resize(m.col);
}

void QLearning::solve()
{
    visited.clear();
    ans.clear();
    int row = m.getRow();
    int col = m.getCol();
    int _times = times;
    while(_times--)                     //训练
    {
        _cSeq++;
        for(int s=0;s < row+col-1;s++)  //以对角线方式遍历
        {
            int r = 0;
            int c = s - r;
            while(r<row && c>0)
            {
                if(c<col && !m.isFixedPoint(r,c)) //只有路和宝箱才需要做决定，其它就over了
                    decision[r][c] = QLearningDecision(r,c);
                r++;
                c--;
            }
        }
    }
#if debug_QLearning
    printDirection();
#endif
    getResult();  
}

Direction QLearning::QLearningDecision(int r, int c)
{
    pair<int,int> curPos = make_pair(r,c);
    double estPay = -INF;
    vector<Direction> directions;
    double pay[5] = {};
    int max_i = DOWN;
    for(int i=UP;i <= LEFT;i++)
    {
        pair<int,int> nextPos = m.getXY(curPos, (Direction)i);
        int x = nextPos.first;
        int y = nextPos.second;
        if(!m.walkable(x,y))
        {
            pay[i] = -INF;
            continue;
        }

        MazeElem elem = m.game_map[x][y];
        pay[i] = (1-LEARNING_RATE)*m.game_map[r][c].value
                + LEARNING_RATE*(elem.reward+DISCOUNT*elem.value);
        if(estPay < pay[i])
        {
            estPay = pay[i];
            max_i = i;
        }

        if(pay[i] > -INF/2)
            directions.push_back(Direction(i));
    }
    //Direction direction = directions[rand()%directions.size()];
    Direction direction = Direction(max_i);
    m.estPoint(r,c,estPay);
    return direction;
}

void QLearning::getResult()
{
    visited.clear();
    pair<int,int> cur_pos = m.getStart();
    while(cur_pos != m.getEnd())
    {
        int x = cur_pos.first;
        int y = cur_pos.second;
        if(visited[cur_pos] == 1)
            break;
        visited[cur_pos] = 1;
        ans.push_back(make_pair(cur_pos, decision[x][y]));
        cur_pos = m.getXY(cur_pos,decision[x][y]);
    }
}

#if debug_global
    void QLearning::printDirection()
    {
        string s[] = {"x", "^", ">", "v", "<"};
        cout << "<Direction table>" << endl;
        for (int i=0;i<m.row;i++)
        {
            for (int j=0;j<m.col;j++)
            {
                if(m.walkable(i,j))
                    cout<<s[decision[i][j]]<<" ";
                else
                    cout<<("0 ");
            }
            cout<<endl;
        }
    }

#endif

#if debug_AI_main
int main()
{
    Maze maze(10,10);
    maze.print();
    
    AI *ai = new QLearning(maze);
    ai->solve();
    ai->m.printValue();

    return 0;
}
#endif
