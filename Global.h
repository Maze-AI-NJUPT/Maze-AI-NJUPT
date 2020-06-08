/**
 * 配置全局信息
 * 
 */
#define debug_global 0                     // 1:debug  0:release
#define debug_Maze_main 0
#define debug_AI_main 0

#define LUXURY 0                    //是否开启宝箱和陷阱
const int GAME_ROW = 17;            //默认地图行数
const int GAME_COL = 17;            //默认地图列数
const int LUCKY_PRICE = 50;         //宝箱价值

enum Direction{
    ERR = 0, UP, RIGHT, DOWN, LEFT
};

/**
 * 格子类型：未定义、墙、路、(陷阱、宝箱)
 */
enum _MazeElem{
    UNDEF, WALL, ROAD, TRAP, LUCKY 
};
