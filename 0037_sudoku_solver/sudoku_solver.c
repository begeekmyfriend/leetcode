#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool valid(int num, int row, int col, int index,
                  bool **rows, bool **cols, bool **boxes)
{
    return !rows[row][num] && !cols[col][num] && !boxes[index][num];
}

static bool dfs(char** board, int size, bool **rows, bool **cols, bool **boxes)
{
    if (size == 9 * 9) {
        return true;
    } else {
        int i;
        bool ok = false;
        int row = size / 9;
        int col = size % 9;
        int index = row / 3 * 3 + col / 3;
        if (board[row][col] == '.') {
            for (i = 1; i <= 9; i++) {
                if (valid(i, row, col, index, rows, cols, boxes)) {
                    /* lock this grid as well as the number */
                    board[row][col] = i + '0';
                    rows[row][i] = true;
                    cols[col][i] = true;
                    boxes[index][i] = true;
                    ok = dfs(board, size + 1, rows, cols, boxes);
                    if (!ok) {
                        /* release this grid as well as the number */
                        rows[row][i] = false;
                        cols[col][i] = false;
                        boxes[index][i] = false;
                        board[row][col] = '.';
                    }
                }
            }
        } else {
            ok = dfs(board, size + 1, rows, cols, boxes);
        }
        return ok;
    }
}

void solveSudoku(char** board, int boardSize, int *boardColSize)
{
    int i, j;
    bool **rows = malloc(boardSize * sizeof(bool *));
    bool **cols = malloc(boardSize * sizeof(bool *));
    bool **boxes = malloc(boardSize * sizeof(bool *));

    for (i = 0; i < boardSize; i++) {
        rows[i] = malloc(10 * sizeof(bool));
        cols[i] = malloc(10 * sizeof(bool));
        boxes[i] = malloc(10 * sizeof(bool));
        memset(rows[i], false, 10 * sizeof(bool));
        memset(cols[i], false, 10 * sizeof(bool));
        memset(boxes[i], false, 10 * sizeof(bool));
    }

    /* Mark whether the grid is available for the number */
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardColSize[i]; j++) {
            if (board[i][j] != '.') {
                int num = board[i][j] - '0';
                int index = i / 3 * 3 + j / 3;
                rows[i][num] = true;
                cols[j][num] = true;
                boxes[index][num] = true;
            }
        }
    }

    dfs(board, 0, rows, cols, boxes);
}

int main(void)
{
    int i, j;
    char **board = malloc(9 * sizeof(char *));
    int *col_sizes = malloc(9 * sizeof(int));

    board[0] = malloc(10);
    board[0][0] = '5';
    board[0][1] = '3';
    board[0][2] = '.';
    board[0][3] = '.';
    board[0][4] = '7';
    board[0][5] = '.';
    board[0][6] = '.';
    board[0][7] = '.';
    board[0][8] = '.';
    board[0][9] = '\0';
    col_sizes[0] = 9;

    board[1] = malloc(10);
    board[1][0] = '6';
    board[1][1] = '.';
    board[1][2] = '.';
    board[1][3] = '1';
    board[1][4] = '9';
    board[1][5] = '5';
    board[1][6] = '.';
    board[1][7] = '.';
    board[1][8] = '.';
    board[1][9] = '\0';
    col_sizes[1] = 9;

    board[2] = malloc(10);
    board[2][0] = '.';
    board[2][1] = '9';
    board[2][2] = '8';
    board[2][3] = '.';
    board[2][4] = '.';
    board[2][5] = '.';
    board[2][6] = '.';
    board[2][7] = '6';
    board[2][8] = '.';
    board[2][9] = '\0';
    col_sizes[2] = 9;

    board[3] = malloc(10);
    board[3][0] = '8';
    board[3][1] = '.';
    board[3][2] = '.';
    board[3][3] = '.';
    board[3][4] = '6';
    board[3][5] = '.';
    board[3][6] = '.';
    board[3][7] = '.';
    board[3][8] = '3';
    board[3][9] = '\0';
    col_sizes[3] = 9;

    board[4] = malloc(10);
    board[4][0] = '4';
    board[4][1] = '.';
    board[4][2] = '.';
    board[4][3] = '8';
    board[4][4] = '.';
    board[4][5] = '3';
    board[4][6] = '.';
    board[4][7] = '.';
    board[4][8] = '1';
    board[4][9] = '\0';
    col_sizes[4] = 9;

    board[5] = malloc(10);
    board[5][0] = '7';
    board[5][1] = '.';
    board[5][2] = '.';
    board[5][3] = '.';
    board[5][4] = '2';
    board[5][5] = '.';
    board[5][6] = '.';
    board[5][7] = '.';
    board[5][8] = '6';
    board[5][9] = '\0';
    col_sizes[5] = 9;

    board[6] = malloc(10);
    board[6][0] = '.';
    board[6][1] = '6';
    board[6][2] = '.';
    board[6][3] = '.';
    board[6][4] = '.';
    board[6][5] = '.';
    board[6][6] = '2';
    board[6][7] = '8';
    board[6][8] = '.';
    board[6][9] = '\0';
    col_sizes[6] = 9;

    board[7] = malloc(10);
    board[7][0] = '.';
    board[7][1] = '.';
    board[7][2] = '.';
    board[7][3] = '4';
    board[7][4] = '1';
    board[7][5] = '9';
    board[7][6] = '.';
    board[7][7] = '.';
    board[7][8] = '5';
    board[7][9] = '\0';
    col_sizes[7] = 9;

    board[8] = malloc(10);
    board[8][0] = '.';
    board[8][1] = '.';
    board[8][2] = '.';
    board[8][3] = '.';
    board[8][4] = '8';
    board[8][5] = '.';
    board[8][6] = '.';
    board[8][7] = '7';
    board[8][8] = '9';
    board[8][9] = '\0';
    col_sizes[8] = 9;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    solveSudoku(board, 9, col_sizes);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
