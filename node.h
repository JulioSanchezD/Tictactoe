#include <stdio.h>

#ifndef TICTACTOE_NODE_H
#define TICTACTOE_NODE_H

typedef struct node {
    char grid[3][3];
    char turn;
    int score;
    int depth;
    int operator_coord[2];
} Node;

void printGrid(char grid[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (row % 1 == 0 && row > 0) puts("---------");
        for (int col = 0; col < 3; col++) {
            if (col % 1 == 0 && col > 0) printf("| ");
            printf("%c ", grid[row][col]);
        }
        puts("");
    }
    puts("");
}

void printNode(Node *node) {
    if (node == NULL) {
        puts("NULL Node");
        return;
    }
    printf("Score: %d\n", node->score);
    printf("Depth: %d\n", node->depth);
    printf("Turn: %c\n", node->turn);
    printf("Operator coordinates: (%d, %d)\n", node->operator_coord[0], node->operator_coord[1]);
    puts("Grid:");
    printGrid(node->grid);
}

// Heuristic function
int getScore(char grid[3][3], char turn) {
    int cost_x, cost_o, found_x, found_o;
    cost_x = cost_o = 0;

    // Check rows
    for (int row = 0; row < 3; row++) {
        found_x = found_o = 0;
        for (int col = 0; col < 3; col++) {
            if (grid[row][col] == 'X') found_x = 1;
            else if (grid[row][col] == 'O') found_o = 1;
        }
        if (found_x && !found_o) cost_x++;
        else if (!found_x && found_o) cost_o++;
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        found_x = found_o = 0;
        for (int row = 0; row < 3; row++) {
            if (grid[row][col] == 'X') found_x = 1;
            else if (grid[row][col] == 'O') found_o = 1;
        }
        if (found_x && !found_o) cost_x++;
        else if (!found_x && found_o) cost_o++;
    }

    // Check first diagonal
    found_x = found_o = 0;
    for (int i = 0; i < 3; i++) {
        if (grid[i][i] == 'X') found_x = 1;
        else if (grid[i][i] == 'O') found_o = 1;
    }
    if (found_x && !found_o) cost_x++;
    else if (!found_x && found_o) cost_o++;

    // Check second diagonal
    int col = 2;
    found_x = found_o = 0;
    for(int row = 0; row < 3; row++) {
        if (grid[row][col] == 'X') found_x = 1;
        else if (grid[row][col] == 'O') found_o = 1;
        col--;
    }
    if (found_x && !found_o) cost_x++;
    else if (!found_x && found_o) cost_o++;

    if (turn == 'X') return cost_x - cost_o;
    else return cost_o - cost_x;
}

#endif //TICTACTOE_NODE_H
