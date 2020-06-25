#include "AI.h"
#include <deque>
/**
 * 获取当前方向的反方向
 */
Direction reverseDirection(Direction d)
{
    return (Direction)(((int)d + 1) % 4 + 1);
}
/**
 * 在命令行打印寻路结果
 */
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
        if (option == 2)
            ans.pop_back();
        else if (option == 0)
            ans.push_back(make_pair(next, reverseDirection(it)));
        visited[next] = 0;
    }

    if (d.size() == 1 && option == 1) //使寻路路径中的叶子结点也能被填充
        ans.push_back(make_pair(p, ERR));
}

#define debug_bfs 0
void Bfs::solve()
{
    visited.clear();

    Maze tmp_m(m);
    AI *tmp;
    pair<int, int> pre;

    deque<pair<int, int>> q;
    q.push_back(m.getStart()); //起点加入队列

    while (!q.empty())
    {
        pair<int, int> p = q.front(); //取出队首
        q.pop_front();

        /*需要从上一位置来到当前位置*/
        if (option == 0)
        {
            tmp_m.start = pre;
            tmp_m.end = p;
            tmp = new Dfs(tmp_m, 2);
            tmp->solve();
            ans.insert(ans.end(), tmp->ans.begin(), tmp->ans.end());
            delete tmp;
        }

#if debug_bfs
        cout << endl
             << "<dfs>" << endl;
        string s[] = {"x", "上", "右", "下", "左"};
        for (auto it : tmp->ans)
            cout << it.first.first << "," << it.first.second << "  " << s[it.second] << endl;
        cout << endl;
#endif

        visited[p] = 1;
        auto d = m.getDirections(p.first, p.second); //获得能访问的方向

#if debug_bfs
        cout << d.size() << " " << s[d[0]] << " " << p.first << ", " << p.second << endl;
#endif

        for (auto it : d)
        {
            pair<int, int> next = m.getXY(p, it); //获得下一步坐标
            if (visited[next] == 1)               //避免往回走
                continue;
            ans.push_back(make_pair(p, it)); //更新寻路结果

#if debug_bfs
            string s[] = {"x", "上", "右", "下", "左"};
            cout << p.first << "," << p.second << "  " << s[it] << endl;
#endif

            Direction reverse = reverseDirection(it); //反方向
            decision[next.first][next.second] = reverse;

            if (next == m.getEnd())
            {
#if debug_bfs
                cout << ans.size() << endl;
#endif
                if (option == 2)
                    getBestPath();
                return;
            }

            ans.push_back(make_pair(next, reverse)); //更新寻路结果，返回上一步

            auto next_d = m.getDirections(next.first, next.second);
            if (next_d.size() == 1 && next_d[0] == reverse)
                ;
            else
                q.push_back(next); //将下一步坐标放到队尾
        }
#if debug_bfs
        cout << endl;
#endif

        pre = p;
    }
}
/**
 * @brief Bfs::getBestPath
 * 从反的方向矩阵中获得最佳路径
 */
void Bfs::getBestPath()
{
    ans.clear();
    pair<int, int> cur_pos = m.getEnd();
    while (cur_pos != m.getStart())
    {
        int x = cur_pos.first;
        int y = cur_pos.second;
        pair<int, int> next_pos = m.getXY(cur_pos, decision[x][y]);
        ans.push_back(make_pair(next_pos, reverseDirection(decision[x][y])));
        cur_pos = next_pos;
    }
    reverse(ans.begin(), ans.end());
}

QLearning::QLearning(Maze maze, bool lambda, int option) : AI(maze, option)
{
    this->lambda = lambda;
    epsilon = EPSILON;
    srand(static_cast<unsigned>(time(NULL)));
    visited.clear();
    this->times = m.row * 2 + 5;
    decision.resize(m.row);
    for (int i = 0; i < m.row; i++)
        decision[i].resize(m.col);
}


/**
 * 遍历所有状态，从每个可用状态开始探索
 */
void QLearning::solve()
{
    visited.clear();
    ans.clear();
    _cSeq = 0;
    int row = m.getRow();
    int col = m.getCol();
    int _times = times;

    getAns = false;
    while (getAns == false)
    {
        for (int s = 0; s < row + col - 1 && !getAns; s++) //以对角线方式遍历所有状态
        {
            int r = 0;
            int c = s - r;
            while (r < row && c > 0)                  //对于所有可用状态
            {
                if (c < col && !m.isFixedPoint(r, c)) //只有路才需要做决定，其它就over了
                {
                    _cSeq++;
                    pair<int, int> start_pos = make_pair(r,c);
                    pair<int,int> end_pos = episode(start_pos);           //一次episode

                    if (getResult() == true)
                    {
                        getAns = true;
                        break;
                    }
                }
                r++;
                c--;
            }
        }
        epsilon = epsilon-0.0001 > 0.001 ? epsilon-0.0001 : 0.001;
    }

#if debug_QLearning
    printDirection();
    cout << "count: " << _cSeq << endl;
#endif
    
}

pair<int, int> QLearning::episode(pair<int,int> st)
{
    trace.clear();
    pair<int, int> cur_pos = st;
    pair<int, int> pre_pos = cur_pos;
    visited.clear();
    int x = cur_pos.first;
    int y = cur_pos.second;

    while (visited[cur_pos] == 0) //一次episode，末态是到达终点或该点已经被访问过
    {
        x = cur_pos.first;
        y = cur_pos.second;
        visited[cur_pos] = 1;

        Direction next_d;
        if(lambda == true)
            next_d = QLambdaDecision(x, y, pre_pos);          //做出动作并更新Q表
        else
            next_d = QLearningDecision(x, y, pre_pos);
        
        if (cur_pos == m.getEnd() || next_d == ERR ) //如果做出非法动作 或 Q表仍为0 则退出这次episode  || m.game_map[x][y].value == 0
            break;

        pre_pos = cur_pos;
        cur_pos = m.getXY(cur_pos, next_d); //获取下一状态
    }

    return cur_pos;
}

Direction QLearning::QLearningDecision(int r, int c, pair<int, int> pre_pos)
{
    pair<int, int> curPos = make_pair(r, c);
    Direction direction;
    double estPay = -INF;
    vector<Direction> directions;
    double pay[5] = {};
    int max_i = ERR;

    for (int i = UP; i <= LEFT; i++)
    {
        pair<int, int> nextPos = m.getXY(curPos, (Direction)i);
        int x = nextPos.first;
        int y = nextPos.second;
        if (!m.walkable(x, y) || nextPos == pre_pos)
        {
            pay[i] = -INF;
            continue;
        }

        MazeElem elem = m.game_map[x][y];
        pay[i] = (1 - LEARNING_RATE) * m.game_map[r][c].value + LEARNING_RATE * (elem.reward + DISCOUNT * elem.value);
        if (estPay < pay[i])
        {
            estPay = pay[i];
            max_i = i;
        }

        if (pay[i] > -INF / 2)
            directions.push_back(Direction(i));
    }
    if (max_i == ERR)
        return ERR;
    direction = Direction(max_i);
    decision[r][c] = direction;

    //采用epsilon-greedy，一定概率智能体不选择最大价值的方向，而是选择其他方向
    if ((rand() / (RAND_MAX + 0.00001)) < epsilon && !directions.empty())
    {
        double rand_d = rand() / (RAND_MAX + 1.00001);
        double rand_div = 1.0 / directions.size();
        for (int i = 0; i < directions.size(); i++)
            if (rand_d < (i + 1) * rand_div)
            {
                direction = directions[i];
                break;
            }
    }

    m.estPoint(r, c, estPay);
    return direction;
}

Direction QLearning::QLambdaDecision(int r, int c, pair<int, int> pre_pos)
{
    pair<int, int> curPos = make_pair(r, c);
    Direction direction;
    double estPay = -INF;
    vector<Direction> directions;
    double pay[5] = {};
    int max_i = ERR;

    trace[curPos] += 1;

    for (int i = UP; i <= LEFT; i++)
    {
        pair<int, int> nextPos = m.getXY(curPos, (Direction)i);
        int x = nextPos.first;
        int y = nextPos.second;
        if (!m.walkable(x, y) || nextPos == pre_pos)
        {
            pay[i] = -INF;
            continue;
        }

        MazeElem elem = m.game_map[x][y];
        pay[i] = m.game_map[r][c].value +
                 LEARNING_RATE * (elem.reward + DISCOUNT * elem.value - m.game_map[r][c].value) * trace[curPos];

        if (estPay < pay[i])
        {
            estPay = pay[i];
            max_i = i;
        }

        if (pay[i] > -INF / 2)
            directions.push_back(Direction(i));
    }
    if (max_i == ERR)
        return ERR;

    direction = Direction(max_i);                      //最大化价值时
    decision[r][c] = direction;
    trace[curPos] *= DISCOUNT * LAMBDA;                //资格迹进行衰减

    //采用epsilon-greedy，一定概率智能体不选择最大价值的方向，而是选择其他方向
    if ((rand() / (RAND_MAX + 0.00001)) < epsilon && !directions.empty())
    {
        double rand_d = rand() / (RAND_MAX + 1.00001);
        double rand_div = 1.0 / directions.size();
        for (int i = 0; i < directions.size(); i++)
            if (rand_d < (i + 1) * rand_div)           //如果随机选择方向
            {
                direction = directions[i];
                trace[curPos] = 0;                     //资格迹置为0
                break;
            }
    }

    m.estPoint(r, c, estPay);
    return direction;
}

bool QLearning::getResult()
{
    visited.clear();
    ans.clear();
    pair<int, int> cur_pos = m.getStart();
    while (cur_pos != m.getEnd())
    {
        int x = cur_pos.first;
        int y = cur_pos.second;
        if (visited[cur_pos] == 1)
            break;
        visited[cur_pos] = 1;
        ans.push_back(make_pair(cur_pos, decision[x][y]));
        if (decision[x][y] == ERR)
            break;
        cur_pos = m.getXY(cur_pos, decision[x][y]);
    }
    if (cur_pos == m.getEnd())
        return true;
    return false;
}

#if debug_global
void QLearning::printDirection()
{
    string s[] = {"x", "^", ">", "v", "<"};
    cout << "<Direction table>" << endl;
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            if (m.walkable(i, j))
                cout << s[decision[i][j]] << " ";
            else
                cout << ("0 ");
        }
        cout << endl;
    }
}

#endif

#if debug_AI_main
int main()
{
    int cases = 10;
    while(cases--)
    //for(int i=7;i<=97;i+=10)
    {
        int i = 53;
        Maze maze(i,i);
        printf("%d: Maze size %dx%d\n",10-cases,i,i);
        QLearning normal(maze,false,2);
        QLearning lambda(maze,true,2);
        lambda.solve();
        printf("QLambda   train count = %d\n",lambda._cSeq);
        normal.solve();
        printf("QLearning train count = %d\n\n",normal._cSeq);
        //lambda.m.printValue();
    }
    // Maze maze(59, 59);
    // maze.print();
    // AI *ai = new QLearning(maze);
    // ai->solve();
    // ai->m.printValue();
    // ai->output();
    return 0;
}
#endif
