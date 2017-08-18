#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct stack {
    int row;
    int col;
    int value;
};

static bool valid(char **board, int row, int col)
{
    int i, j, k;
    char mark[10];

    for (i = 0; i <= row; i++) {
        memset(mark, 0, 10);
        /* check row validity */
        for (j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int index = board[i][j] - '0';
                if (mark[index]) {
                    return false;
                } else {
                    mark[index] = 1;
                }
            }
        }
    }

    /* check column validity */
    for (i = 0; i <= col; i++) {
        memset(mark, 0, 10);
        for (j = 0; j < 9; j++) {
            if (board[j][i] != '.') {
                int index = board[j][i] - '0';
                if (mark[index]) {
                    return false;
                } else {
                    mark[index] = 1;
                }
            }
        }
    }

    /* check sub-box validity */
    int count = row / 3 * 3 + col / 3 + 1;
    for (k = 0; k < count; k++) {
        int sr = k / 3 * 3;
        int sc = (k % 3) * 3;
        memset(mark, 0, 10);
        for (i = sr; i < sr + 3; i++) {
            for (j = sc; j < sc + 3; j++) {
                if (board[i][j] != '.') {
                    int index = board[i][j] - '0';
                    if (mark[index]) {
                        return false;
                    } else {
                        mark[index] = 1;
                    }
                }
            }
        }
    }

    return true;
}

static void solveSudoku(char** board, int boardRowSize, int boardColSize)
{
    if (boardRowSize != 9 || boardColSize != 9) {
        return;
    }

    int i = 0, j = 0, k = 1, num = 0;
    struct stack stack[81];

    while (i < boardRowSize) {
        if (board[i][j] == '.') {
            while (k <= 9) {
                board[i][j] = k + '0';
                if (valid(board, i, j)) {
                    stack[num].row = i;
                    stack[num].col = j;
                    stack[num].value = k;
                    num++;
                    k = 1;
                    break;
                }
                k++;
            }
            if (k == 10) {
                if (num == 0) {
                    return;
                }                
                board[i][j] = '.';
                --num;
                i = stack[num].row;
                j = stack[num].col;
                k = stack[num].value + 1;
                board[i][j] = '.';
                continue;
            }
        }
        /* next row */
        if (++j == boardColSize) {
            j = 0;
            i++;
        }
    }
}

int main(void)
{
    int i, j;
    char **board = malloc(9 * sizeof(char *));
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

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    solveSudoku(board, 9, 9);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    return;
}
