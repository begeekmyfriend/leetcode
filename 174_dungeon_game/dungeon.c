#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int calculateMinimumHP(int** dungeon, int dungeonRowSize, int dungeonColSize)
{
    int i, j;
    int **dp = malloc(dungeonRowSize * sizeof(int *));
    for (i = 0; i < dungeonRowSize; i++) {
        dp[i] = malloc(dungeonColSize * sizeof(int));
    }

    for (i = dungeonRowSize - 1; i >= 0; i--) {
        for (j = dungeonColSize - 1; j >= 0; j--) {
            if (i == dungeonRowSize - 1 && j == dungeonColSize - 1) {
                dp[i][j] = 1 - dungeon[i][j] > 1 ? 1 - dungeon[i][j] : 1;
            } else {
                int hp1 = i == dungeonRowSize - 1 ? INT_MAX : (dp[i + 1][j] - dungeon[i][j] > 1 ? dp[i + 1][j] - dungeon[i][j] : 1);
                int hp2 = j == dungeonColSize - 1 ? INT_MAX : (dp[i][j + 1] - dungeon[i][j] > 1 ? dp[i][j + 1] - dungeon[i][j] : 1);
                dp[i][j] = hp1 < hp2 ? hp1 : hp2;
            }
        }
    }

    return dp[0][0];
}

int main(void)
{
    int row_size = 3, col_size = 3;
    int i, j, **dungeon = malloc(row_size * sizeof(int *));
    for (i = 0; i < row_size; i++) {
        dungeon[i] = malloc(col_size * sizeof(int));
    }
#if 1
    dungeon[0][0] = 1;
    dungeon[0][1] = -3;
    dungeon[0][2] = 3;
    dungeon[1][0] = 0;
    dungeon[1][1] = -2;
    dungeon[1][2] = 0;
    dungeon[2][0] = -3;
    dungeon[2][1] = -3;
    dungeon[2][2] = -3;
#else
    dungeon[0][0] = 3;
    dungeon[0][1] = -20;
    dungeon[0][2] = 30;
    dungeon[1][0] = -3;
    dungeon[1][1] = 4;
    dungeon[1][2] = 0;
#endif

    printf("dungeon:\n");
    for (i = 0; i < row_size; i++) {
        for (j = 0; j < col_size; j++) {
            printf("%d ", dungeon[i][j]);
        }
        printf("\n");
    }
    printf("%d\n", calculateMinimumHP(dungeon, row_size, col_size));
    return 0;
}
