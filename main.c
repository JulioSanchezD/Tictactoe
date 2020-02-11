#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

typedef enum {
    easy = 1, medium = 3, hard = 5, ultrahard = 10
} Level;
Level level;
int r_row, r_col;


int negamax(Node *parent) {
    //printNode(parent);
    char turn = (parent->turn == 'O') ? 'X' : 'O';
    int cont, n_siblings, depth, res;
    cont = 0;
    depth = parent->depth + 1;
    n_siblings = countBlankSpaces(parent->grid);
    Node *siblings[n_siblings];
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (parent->grid[row][col] == ' ') {
                siblings[cont++] = newNode(parent->grid, turn, depth, row, col);
            }
        }
    }
    int max, score;
    max = -200;
    Node *max_sibling;
    for (int i = 0; i < n_siblings; i++) {
        if (depth == level || n_siblings == 1 || siblings[i]->score == abs(100)) {
            score = siblings[i]->score;
        } else {
            score = negamax(siblings[i]);
        }
        if (score > max) {
            max = score;
            max_sibling = siblings[i];
        }
        if (score == 100) break;
    }
    r_row = max_sibling->operator_coord[0];
    r_col = max_sibling->operator_coord[1];
    freeSiblings(siblings, n_siblings);
    return -max;
}

int main() {
    setbuf(stdout, 0);
    int row, col;
    char grid[3][3] = {{"   "},
                       {"   "},
                       {"   "}};
    level = ultrahard;
    do {
        printGrid(grid);
        printf("Enter your move (row, column): ");
        scanf("%d %d", &row, &col);
        if (grid[row][col] == ' ') {
            Node *root = newNode(grid, 'O', 0, row, col);
            if (countBlankSpaces(root->grid) > 0){
                negamax(root);
                grid[r_row][r_col] = 'X';
            }
            grid[row][col] = 'O';
        }
        else {
            printf("Bad input, please enter other location\n");
        }
    } while (countBlankSpaces(grid) != 0 && getScore(grid, 'X') != abs(100));
    printGrid(grid);
    if (getScore(grid, 'O') == -100) printf("Congratulations, you won!\n");
    else if (getScore(grid, 'O') == 100) printf("Computer won!\n");
    else printf("It's a draw!\n");
    return 0;
}
