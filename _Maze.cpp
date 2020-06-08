#include "_Maze.h"
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
    initialMaze(row,col);
    genMap();
    initialMapStytle();
}

void Maze::initialMaze(int row,int col)
{
    if (row %2 == 0 || col %2 ==0)
        row++, col++;

    this->row = row;
    this->col = col;
    game_map.resize(row);
    for (int i = 0; i < row; i++)
        game_map[i].resize(col);
}

void Maze::initialMapStytle() //初始化地图风格字符串
{
    MapStytle[0][0]="border-image: url(:/new/image/MagicGril/down1.png);";
    MapStytle[0][1]="border-image: url(:/new/image/MagicGril/down2.png);";
    MapStytle[0][2]="border-image: url(:/new/image/MagicGril/down3.png);";
    MapStytle[0][3]="border-image: url(:/new/image/MagicGril/up1.png);";
    MapStytle[0][4]="border-image: url(:/new/image/MagicGril/up2.png);";
    MapStytle[0][5]="border-image: url(:/new/image/MagicGril/up3.png);";
    MapStytle[0][6]="border-image: url(:/new/image/MagicGril/left1.png);";
    MapStytle[0][7]="border-image: url(:/new/image/MagicGril/left2.png);";
    MapStytle[0][8]="border-image: url(:/new/image/MagicGril/left3.png);";
    MapStytle[0][9]="border-image: url(:/new/image/MagicGril/right1.png);";
    MapStytle[0][10]="border-image: url(:/new/image/MagicGril/right2.png);";
    MapStytle[0][11]="border-image: url(:/new/image/MagicGril/right3.png);";
    MapStytle[0][12]="border-image: url(:/new/image/MagicGril/Wall.png);";
    MapStytle[0][13]="border-image: url(:/new/image/MagicGril/Load.png);";
    MapStytle[0][14]="border-image: url(:/new/image/MagicGril/box.png);";
    MapStytle[0][15]="border-image: url(:/new/image/MagicGril/MagicGrill.png);";

    MapStytle[1][0]="border-image: url(:/Naruto/image/Naruto/down1.png);";
    MapStytle[1][1]="border-image: url(:/Naruto/image/Naruto/down2.png);";
    MapStytle[1][2]="border-image: url(:/Naruto/image/Naruto/down3.png);";
    MapStytle[1][3]="border-image: url(:/Naruto/image/Naruto/up1.png);";
    MapStytle[1][4]="border-image: url(:/Naruto/image/Naruto/up2.png);";
    MapStytle[1][5]="border-image: url(:/Naruto/image/Naruto/up3.png);";
    MapStytle[1][6]="border-image: url(:/Naruto/image/Naruto/left1.png);";
    MapStytle[1][7]="border-image: url(:/Naruto/image/Naruto/left2.png);";
    MapStytle[1][8]="border-image: url(:/Naruto/image/Naruto/left3.png);";
    MapStytle[1][9]="border-image: url(:/Naruto/image/Naruto/right1.png);";
    MapStytle[1][10]="border-image: url(:/Naruto/image/Naruto/right2.png);";
    MapStytle[1][11]="border-image: url(:/Naruto/image/Naruto/right3.png);";
    MapStytle[1][12]="border-image: url(:/Naruto/image/Naruto/Wall.png);";
    MapStytle[1][13]="border-image: url(:/Naruto/image/Naruto/Load.png);";
    MapStytle[1][14]="border-image: url(:/Naruto/image/Naruto/box.png);";
    MapStytle[1][15]="border-image: url(:/Naruto/image/Naruto/Naruto.png);";

    MapStytle[2][0]="border-image: url(:/SuperMarie/image/SuperMarie/down1.png);";
    MapStytle[2][1]="border-image: url(:/SuperMarie/image/SuperMarie/down2.png);";
    MapStytle[2][2]="border-image: url(:/SuperMarie/image/SuperMarie/down3.png);";
    MapStytle[2][3]="border-image: url(:/SuperMarie/image/SuperMarie/up1.png);";
    MapStytle[2][4]="border-image: url(:/SuperMarie/image/SuperMarie/up2.png);";
    MapStytle[2][5]="border-image: url(:/SuperMarie/image/SuperMarie/up3.png);";
    MapStytle[2][6]="border-image: url(:/SuperMarie/image/SuperMarie/left1.png);";
    MapStytle[2][7]="border-image: url(:/SuperMarie/image/SuperMarie/left2.png);";
    MapStytle[2][8]="border-image: url(:/SuperMarie/image/SuperMarie/left3.png);";
    MapStytle[2][9]="border-image: url(:/SuperMarie/image/SuperMarie/right1.png);";
    MapStytle[2][10]="border-image: url(:/SuperMarie/image/SuperMarie/right2.png);";
    MapStytle[2][11]="border-image: url(:/SuperMarie/image/SuperMarie/right3.png);";
    MapStytle[2][12]="border-image: url(:/SuperMarie/image/SuperMarie/Wall.png);";
    MapStytle[2][13]="border-image: url(:/SuperMarie/image/SuperMarie/Load.png);";
    MapStytle[2][14]="border-image: url(:/SuperMarie/image/SuperMarie/box.png);";
    MapStytle[2][15]="border-image: url(:/SuperMarie/image/SuperMarie/SuperMarie.png);";
}


void Maze::setCharacterPos()
{
    //随机设定方式
//   point temp;
//   QStack<point> s;
//   for(int i=0;i<height;i++)
//   {
//       for(int j=0;j<width;j++)
//       {
//           if(Matrix[i][j].state==1)
//           {
//               temp.i=i;
//               temp.j=j;
//               s.push(temp);
//           }
//       }
//   }
//   int randNum=qrand()%s.size();
//   x=s[randNum].i;
//   y=s[randNum].j;
   gamer.first=3;
   gamer.second=3;
}
void Maze::setExitPos()
{
    //随机设定方式
//    point temp;
//    QStack<point> s;
//    for(int i=0;i<height;i++)
//    {
//        for(int j=0;j<width;j++)
//        {
//            if(Matrix[i][j].state==1)
//            {
//                temp.i=i;
//                temp.j=j;
//                s.push(temp);
//            }
//        }
//    }
//    while(true)
//    {
//        int randNum=qrand()%s.size();
//        exit_x=s[randNum].i;
//        exit_y=s[randNum].j;
//        if(exit_x!=x||exit_y!=y)
//        {
//            break;
//        }
//    }
    /*
    pair<int,int> ed;
    do
    {
        ed = genGap(time(NULL));
    } while (game_map[ed.first][ed.second].getType() == WALL);
    this->end = ed;
    */
    this->end = make_pair(row-2,col-2);
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
    st = make_pair(3,3);

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


    setExitPos();
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
