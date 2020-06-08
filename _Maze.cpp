#include "Maze.h"
#include <time.h>
#include <map>
#include <assert.h>

MazeElem::MazeElem(_MazeElem type = ROAD)
{
    if (type == LUCKY)
        value = LUCKY_PRICE;
    else
    {
        this->type = type;
        value = 0;
    }
}

void MazeElem::setType(_MazeElem tp)
{
    this->type = tp;
    if (tp == LUCKY)
        value = LUCKY_PRICE;
    else
        value = 0;
}

_MazeElem MazeElem::getType() { return type; }

bool MazeElem::operator==(_MazeElem type)
{
    return this->type == type;
}

Maze::Maze(int row = GAME_ROW, int col = GAME_COL)
{
    if (row %2 == 0 || col %2 ==0)
        row++, col++;

    this->row = row;
    this->col = col;
    game_map.resize(row);
    for (int i = 0; i < row; i++)
        game_map[i].resize(col);
    genMap();
}

vector<vector<MazeElem>> Maze::getMap() { return game_map; }

int Maze::getRow() { return row; }

int Maze::getCol() { return col; }

Maze::~Maze() {}

bool Maze::walkable(int x, int y)
{
    if (x >= row || x < 0 || y >= col || y < 0)
        return false;

    _MazeElem d = game_map[x][y].getType();
    if (d == ROAD || d == LUCKY)
        return true;

    return false;
}

vector<Direction> Maze::getDirections(int x, int y)
{
    vector<Direction> direction;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++)
    {
        if (walkable(x + dx[i], y + dy[i]))
            direction.push_back((Direction)(i + 1));
    }
    return direction;
}

void Maze::getWall(int x, int y, vector<pair<pair<int,int>,Direction>> &blocks)
{
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++)
    {
        if (x + dx[i] > row-2 || x + dx[i] < 1 || y + dy[i] > col-2 || y + dy[i] < 1)
            continue;
        if (!walkable(x + dx[i], y + dy[i]))
            blocks.push_back(make_pair(make_pair(x + dx[i], y + dy[i]),(Direction)(i + 1)));
    }
}

#define debug_genGap 0
pair<int, int> Maze::genGap(unsigned int _Seed)
{
    //srand(_Seed);
    pair<int, int> st;
    int x = rand() % (row-2) + 1;
    int y = rand() % (col-2) + 1;
    st = make_pair(x, y);
    return st;
}

pair<int, int> Maze::getXY(pair<int, int> point, Direction now)
{
    int dx[5] = {10, -1, 0, 1, 0};
    int dy[5] = {10, 0, 1, 0, -1};
    int x = point.first + dx[(int)now];
    int y = point.second + dy[(int)now];
    return make_pair(x, y);
}

#define debug_genMap 1
// 随机prime构造迷宫
void Maze::genMap()
{
#if LUXURY
    int flag = 4;
#else
    int flag = 2;
#endif

    srand(time(NULL)); //随机种子
    pair<int, int> st;
    /*设成了（1，1）*/
    st = make_pair(1,1);

    this->start = st;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            game_map[i][j].setType(WALL);
    
    game_map[st.first][st.second].setType(ROAD); //定义起点

    int x = st.first, y = st.second;
    vector<pair<pair<int,int>,Direction>> blocks;
    getWall(x, y, blocks);                  //获取与起点相邻的墙体（除去越界的）

    while (blocks.size())
    {
        int sz = blocks.size();
        int rand_num = rand() % sz;
        // 获得相邻的墙体
        x = blocks[rand_num].first.first;
        y = blocks[rand_num].first.second;
        
        // 穿墙。起点->(x,y)->(x1,y1)构成一条直线
        pair<int, int> point = make_pair(x, y);
        point = getXY(point, blocks[rand_num].second);
        int x1 = point.first, y1 = point.second;

        if (game_map[x1][y1].getType() == WALL)
        {
            game_map[x1][y1].setType(ROAD);
            game_map[x][y].setType(ROAD);
            getWall(x1, y1, blocks);
        }

        blocks.erase(blocks.begin() + rand_num);
    }

    pair<int,int> ed;
    do
    {
        ed = genGap(time(NULL));
    } while (game_map[ed.first][ed.second].getType() == WALL);
    this->end = ed;
}

#if debug_Maze_main
int main()
{
    Maze maze(32,32);
    maze.print();
    maze.genMap();
    maze.print();
}
#endif
