#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

int main() {
    char grid[3][3] = {{" OX"},
                       {" X "},
                       {"O  "}};

    Node *root = (Node *) malloc(sizeof(Node));
    memcpy(root->grid, grid, sizeof(grid));
    root->turn = 'X';
    root->score = getScore(grid, root->turn);
    root->depth = 0;
    root->operator_coord[0] = 2;
    root->operator_coord[1] = 0;

    printNode(root);
    return 0;
}
