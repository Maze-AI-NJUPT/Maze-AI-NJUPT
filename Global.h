/* 配置全局信息 */
#define debug_global 1              // 1 -> debug, 0 -> release
#define debug_Maze_main 0           //debug _Maze.cpp
#define debug_AI_main 0             //debug AI.cpp
#define debug_QLearning 0

#include<QDebug>

const int INF = 0x3f4f5f6f;

#define LUXURY 0                    //是否开启宝箱和陷阱
const int GAME_ROW = 17;            //默认地图行数
const int GAME_COL = 17;            //默认地图列数
const int LUCKY_PRICE = 50;         //宝箱价值

/* 方向 */
enum Direction{
    ERR = 0, UP, RIGHT, DOWN, LEFT
};

/* 格子类型：未定义、墙、路、(陷阱、宝箱) */
enum _MazeElem{
    UNDEF, WALL, ROAD, TRAP, LUCKY
};

/* 强化学习参数 */
const double LEARNING_RATE = 0.9;   //学习率
const double DISCOUNT = 0.99;       //折扣因子
//const double EPSILON = 1;
const int TIMES = 125;              //训练次数(不使用，根据地图大小自适应)

const double V_DEST = 1;            //终点奖励
const double V_TRAP = -1;           //陷阱奖励
const double V_ROAD = 0;
const double V_WALL = -1;
const double V_LUCKY = 0.5;         //宝箱奖励
