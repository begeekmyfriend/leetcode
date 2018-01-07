#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool dfs(char *word, char **board, bool *used,
                int row, int col, int row_size, int col_size)
{
    if (board[row][col] != *word) {
        return false;
    }

    used[row * col_size + col] = true;

    if (*(word + 1) == '\0') {
        return true;
    }

    bool result = false;
    if (row > 0 && !used[(row - 1) * col_size + col]) {
        result = dfs(word + 1, board, used, row - 1, col, row_size, col_size);
    }

    if (!result && row < row_size - 1 && !used[(row + 1) * col_size + col]) {
        result = dfs(word + 1, board, used, row + 1, col, row_size, col_size);
    }

    if (!result && col > 0 && !used[row * col_size + col - 1]) {
        result = dfs(word + 1, board, used, row, col - 1, row_size, col_size);
    }

    if (!result && col < col_size - 1 && !used[row * col_size + col + 1]) {
        result = dfs(word + 1, board, used, row, col + 1, row_size, col_size);
    }

    used[row * col_size + col] = false;
    return result;
}

static bool exist(char** board, int boardRowSize, int boardColSize, char* word)
{
    int i, j;
    int len = strlen(word);
    if (len > boardRowSize * boardColSize) {
        return false;
    }
    bool *used = malloc(boardRowSize * boardColSize);
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            memset(used, false, boardRowSize * boardColSize);
            if (dfs(word, board, used, i, j, boardRowSize, boardColSize)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test word row1 row2...\n");
        exit(-1);
    }
    printf("%s\n", exist(argv + 2, argc - 2, strlen(argv[2]), argv[1]) ? "true" : "false"
);
    return 0;
}
