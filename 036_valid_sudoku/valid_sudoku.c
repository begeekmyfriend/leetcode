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

static bool isValidSudoku(char** board, int boardRowSize, int boardColSize)
{
    if (boardRowSize != 9 || boardColSize != 9) {
        return false;
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
                    return false;
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

    return true;
}

int main(int argc, char **argv)
{
    int i, j;
    char *str = argv[1];
    char **board = malloc(9 * sizeof(char *));
    for (i = 0; i < 9; i++) {
        board[i] = malloc(10);
        memcpy(board[i], str + i * 9, 9);
        board[9] = '\0';
        char *row = board[i];
        for (j = 0; j < 9; j++) {
            printf("%c ", row[j]);
        }
        printf("\n");
    }
    printf("%s\n", isValidSudoku(board, 9, 9) ? "true" : "false");
    for (i = 0; i < 9; i++) {
        char *row = board[i];
        for (j = 0; j < 9; j++) {
            printf("%c ", row[j]);
        }
        printf("\n");
    }
    return;
}
