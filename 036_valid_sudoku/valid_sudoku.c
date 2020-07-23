#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static bool valid(char **board, char *mark, int i, int j) {
    if (board[i][j] != '.') {
        int index = board[i][j] - '0';
        if (mark[index]) {
            return false;
        } else {
            mark[index] = 1;
        }
    }
    return true;
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{
    int i, j, k;

    /* check row validity */
    for (i = 0; i < boardSize; i++) {
        char mark[10] = { '\0' };
        for (j = 0; j < boardColSize[i]; j++) {
            if (!valid(board, mark, i, j)) {
                return false;
            }
        }
    }

    /* check column validity */
    for (j = 0; j < boardColSize[0]; j++) {
        char mark[10] = { '\0' };
        for (i = 0; i < boardSize; i++) {
            if (!valid(board, mark, i, j)) {
                return false;
            }
        }
    }

    /* check sub-box validity */
    for (k = 0; k < boardSize; k++) {
        int sr = k / 3 * 3;
        int sc = (k % 3) * 3;
        char mark[10] = { '\0' };
        for (i = sr; i < sr + 3; i++) {
            for (j = sc; j < sc + 3; j++) {
                if (!valid(board, mark, i, j)) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

int main(int argc, char **argv)
{
    int i, j;
    char *str = argv[1];
    int *col_sizes = malloc(9 * sizeof(int));
    char **board = malloc(9 * sizeof(char *));
    for (i = 0; i < 9; i++) {
        board[i] = malloc(10);
        strcpy(board[i], str + i * 9);
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        col_sizes[i] = 9;
        printf("\n");
    }

    printf("%s\n", isValidSudoku(board, 9, col_sizes) ? "true" : "false");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
