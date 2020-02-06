#include <stdio.h>

#ifndef TICTACTOE_NODE_H
#define TICTACTOE_NODE_H

typedef struct node {
    int grid[3][3];
    int score;
} Node;

// Heuristic function
int getScore(int grid[3][3], int turn) {
    int cost_1, cost_2, found_1, found_2;
    cost_1 = cost_2 = 0;

    // Check rows
    for (int row = 0; row < 3; row++) {
        found_1 = found_2 = 0;
        for (int col = 0; col < 3; col++) {
            if (grid[row][col] == 1) found_1 = 1;
            else if (grid[row][col] == 2) found_2 = 1;
        }
        if (found_1 && !found_2) cost_1++;
        else if (!found_1 && found_2) cost_2++;
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        found_1 = found_2 = 0;
        for (int row = 0; row < 3; row++) {
            if (grid[row][col] == 1) found_1 = 1;
            else if (grid[row][col] == 2) found_2 = 1;
        }
        if (found_1 && !found_2) cost_1++;
        else if (!found_1 && found_2) cost_2++;
    }

    // Check first diagonal
    found_1 = found_2 = 0;
    for (int i = 0; i < 3; i++) {
        if (grid[i][i] == 1) found_1 = 1;
        else if (grid[i][i] == 2) found_2 = 1;
    }
    if (found_1 && !found_2) cost_1++;
    else if (!found_1 && found_2) cost_2++;

    // Check second diagonal
    int col = 2;
    found_1 = found_2 = 0;
    for(int row = 0; row < 3; row++) {
        if (grid[row][col] == 1) found_1 = 1;
        else if (grid[row][col] == 2) found_2 = 1;
        col--;
    }
    if (found_1 && !found_2) cost_1++;
    else if (!found_1 && found_2) cost_2++;

    if (turn == 1) return cost_1 - cost_2;
    else return cost_2 - cost_1;
}

#endif //TICTACTOE_NODE_H
