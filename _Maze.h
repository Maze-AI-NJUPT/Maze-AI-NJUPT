#include<memory>
#include<vector>
#include<iostream>
#include<QString>
#include"Global.h"
using namespace std;

/**
 * 地图中的格子
 */
class MazeElem
{
private:
    _MazeElem type;                         //格子类型
    int value;                              //格子价值
public:
    MazeElem(_MazeElem type);
    _MazeElem getType();
    void setType(_MazeElem tp);

    bool operator==(_MazeElem type);
};

/**
 * 地图
 */
class Maze
{
private:
    pair<int,int> start;                    //入口坐标
public:
    int row;                                //行数
    int col;                                //列数
    pair<int,int> gamer;                    //角色坐标
    pair<int,int> end;                      //出口坐标
    vector<vector<MazeElem>> game_map;      //地图
    QString MapStytle[4][22];//地图风格字符串
public:
    Maze(int row, int col);
    Maze(){initialMaze(GAME_ROW,GAME_COL);  genMap(); initialMapStytle();}
    ~Maze();

    void genMap();                           //生成随机地图
    vector<vector<MazeElem>> getMap();       //获取地图
    int getRow();                            //获取地图行数
    int getCol();                            //获取地图列数
    pair<int,int> getStart(){return start;}
    pair<int,int> getEnd(){return end;}
    pair<int,int> genGap(unsigned int _Seed); //随机生成入口和出口

    bool walkable(int x,int y);              //(x,y)是否不为墙

    vector<Direction> getDirections(int x, int y);//返回在当前坐标下一步能走的方向
    
    void getWall(int x, int y,vector<pair<pair<int,int>,Direction>> &blocks); //返回坐标相邻的墙体
    pair<int,int> getXY(pair<int,int> point, Direction now); //给出当前坐标和方向，返回下一步坐标
    
    //移植QT
    void initialMaze(int row,int col);
    void initialMapStytle();//初始化地图风格字符串
    void setCharacterPos();//设置角色位置
    void setExitPos();

#if debug
    void print();                             //[测试]:在命令行中打印迷宫
#endif
};

#if debug
void Maze::print()
{
    cout << "<迷宫打印>" << endl;
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<row;j++)
        {
            char ch;
            switch (game_map[i][j].getType())
            {
            case ROAD:
                ch = ' ';
                break;
            case LUCKY:
                ch = '$';
                break;
            case WALL:
                ch = '*';
                break;
            case TRAP:
                ch = 'O';
                break;
            default:
                ch = 'X';
                break;
            } 
            if(i == start.first && j == start.second)
                ch = '@';
            else if(i == end.first && j == end.second)
                ch = 'O';
            cout<<ch;
        }
        cout<<endl;
    }
    cout<<endl;
}
#endif
