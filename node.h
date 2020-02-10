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
            if (grid[row][col] == 'X') found_x++;
            else if (grid[row][col] == 'O') found_o++;
        }
        if (found_x == 3 || found_o == 3) return 100;
        else if (found_x && !found_o) cost_x++;
        else if (!found_x && found_o) cost_o++;
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        found_x = found_o = 0;
        for (int row = 0; row < 3; row++) {
            if (grid[row][col] == 'X') found_x++;
            else if (grid[row][col] == 'O') found_o++;
        }
        if (found_x == 3 || found_o == 3) return 100;
        else if (found_x && !found_o) cost_x++;
        else if (!found_x && found_o) cost_o++;
    }

    // Check first diagonal
    found_x = found_o = 0;
    for (int i = 0; i < 3; i++) {
        if (grid[i][i] == 'X') found_x++;
        else if (grid[i][i] == 'O') found_o++;
    }
    if (found_x == 3 || found_o == 3) return 100;
    else if (found_x && !found_o) cost_x++;
    else if (!found_x && found_o) cost_o++;

    // Check second diagonal
    int col = 2;
    found_x = found_o = 0;
    for (int row = 0; row < 3; row++) {
        if (grid[row][col] == 'X') found_x++;
        else if (grid[row][col] == 'O') found_o++;
        col--;
    }
    if (found_x == 3 || found_o == 3) return 100;
    if (found_x && !found_o) cost_x++;
    else if (!found_x && found_o) cost_o++;

    if (turn == 'X') return cost_x - cost_o;
    else return cost_o - cost_x;
}

Node *newNode(char grid[3][3], char turn, int depth, int row_coord, int col_coord) {
    Node *node = (Node *) malloc(sizeof(Node));
    memcpy(node->grid, grid, sizeof(char[3][3]));
    node->grid[row_coord][col_coord] = turn;
    node->score = getScore(node->grid, turn);
    node->turn = turn;
    node->depth = depth;
    node->operator_coord[0] = row_coord;
    node->operator_coord[1] = col_coord;
    return node;
}

int countBlankSpaces(char grid[3][3]) {
    int cont = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row][col] == ' ') cont++;
        }
    }
    return cont;
}

void freeSiblings(Node *siblings[], int n_siblings) {
    for (int i = 0; i < n_siblings; i++) {
        free(siblings[i]);
    }
}

#endif //TICTACTOE_NODE_H
