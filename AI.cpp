#include "AI.h"

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