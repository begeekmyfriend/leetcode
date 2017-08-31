#include <stdio.h>
#include <stdlib.h>

/**
 ** Return an array of arrays.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** generateMatrix(int n) {
    int i;
    int **matrix = malloc(n * sizeof(int *));
    int *nums = malloc(n * n * sizeof(int));
    for (i = 0; i < n; i++) {
        matrix[i] = &nums[i * n];
    }

    int direction = 0;
    int hor_top = 0;
    int hor_bottom = n - 1;
    int ver_left = 0;
    int ver_right = n - 1;
    int num  = 0;
    while (num < n * n) {
        switch (direction) {
        case 0:
            for (i = ver_left; i <= ver_right; i++) {
                 matrix[hor_top][i] = ++num;
            }
            hor_top++;
            break;
        case 1:
            for (i = hor_top; i <= hor_bottom; i++) {
                 matrix[i][ver_right] = ++num;
            }
            ver_right--;
            break;
        case 2:
            for (i = ver_right; i >= ver_left; i--) {
                 matrix[hor_bottom][i] = ++num;
            }
            hor_bottom--;
            break;
        case 3:
            for (i = hor_bottom; i >= hor_top; i--) {
                 matrix[i][ver_left] = ++num;
            }
            ver_left++;
            break;
        }
        direction++;
        direction %= 4;
    }

    return matrix;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    int i, j;
    int n = atoi(argv[1]);
    int **matrix = generateMatrix(n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
