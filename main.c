#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"

typedef enum {
    easy = 3, medium = 5, ultrahard = 10
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

int random_1(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main() {
    setbuf(stdout, 0);
    int row, col, res;
    char grid[3][3] = {{"   "},
                       {"   "},
                       {"   "}};

    // Ask for difficulty level
    level = ultrahard;
    int i_level;
    printf("Select difficulty level (3->easy, 5->medium, 10->unbeatable): ");
    scanf("%d", &i_level);
    level = (Level) i_level;

    // Ask if player wants to play the first move
    res = 0;
    printf("Do you want to play the first move (1->yes, 0->no)?: ");
    scanf("%d", &res);

    // Let computer play first move
    if (!res) {
        srand (time (0));
        Node *root = newNode(grid, 'X', 0, random_1(0, 2), random_1(0, 2));
        negamax(root);
        grid[r_row][r_col] = 'X';
    }

    // Play the game
    do {
        printGrid(grid);
        printf("Enter your move (row, column): ");
        scanf("%d %d", &row, &col);
        if (grid[row][col] == ' ' || row > 2 || col > 2) {
            Node *root = newNode(grid, 'O', 0, row, col);
            if (countBlankSpaces(root->grid) > 0){
                negamax(root);
                grid[r_row][r_col] = 'X';
            }
            grid[row][col] = 'O';
        }
        else {
            printf("Bad input, please enter other location between [0, 2]\n");
        }
    } while (countBlankSpaces(grid) != 0 && getScore(grid, 'X') != 100 && getScore(grid, 'O') != 100);

    // Show results
    printGrid(grid);
    if (getScore(grid, 'O') == 100) printf("Congratulations, you won!\n");
    else if (getScore(grid, 'X') == 100) printf("Computer won!\n");
    else printf("It's a draw!\n");
    return 0;
}
