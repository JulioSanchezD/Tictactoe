#include <stdio.h>
#include "node.h"

int main() {
    int grid[3][3] = {{0, 2, 0},
                      {0, 1, 0},
                      {0, 0, 0}};
    int grid2[3][3] = {{0, 2, 1},
                       {0, 1, 0},
                       {2, 0, 0}};
    printf("%d", getScore(grid, 1));
    return 0;
}
