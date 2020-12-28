#include <stdio.h>
#include <stdlib.h>

static int calculateMinimumHP(int** dungeon, int dungeonRowSize, int dungeonColSize)
{
    int i, j;
    int **dp = malloc(dungeonRowSize * sizeof(int *));
    for (i = 0; i < dungeonRowSize; i++) {
        dp[i] = malloc(dungeonColSize * sizeof(int));
    }

    int hp = 1 - dungeon[dungeonRowSize - 1][dungeonColSize - 1];
    dp[dungeonRowSize - 1][dungeonColSize - 1] = hp >= 1 ? hp : 1;
    for (i = dungeonRowSize - 2; i >= 0; i--) {
        hp = dp[i + 1][dungeonColSize - 1] - dungeon[i][dungeonColSize - 1];
        dp[i][dungeonColSize - 1] = hp >= 1 ? hp : 1;
    }

    for (i = dungeonColSize - 2; i >= 0; i--) {
        hp = dp[dungeonRowSize - 1][i + 1] - dungeon[dungeonRowSize - 1][i];
        dp[dungeonRowSize - 1][i] = hp >= 1 ? hp : 1;
    }

    for (i = dungeonRowSize - 2; i >= 0; i--) {
        for (j = dungeonColSize - 2; j >= 0; j--) {
            int hp_r = dp[i][j + 1] - dungeon[i][j];
            int hp_d = dp[i + 1][j] - dungeon[i][j];
            hp_r = hp_r >= 1 ? hp_r : 1;
            hp_d = hp_d >= 1 ? hp_d : 1;
            dp[i][j] = hp_r < hp_d ? hp_r : hp_d;
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
