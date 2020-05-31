#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


static inline int conflict(int *stack, int row, int col)
{
    int i;
    for (i = 0; i < row; i++) {
        /* If occupied or in one line */
        if (col == stack[i] || abs(row - i) == abs(col - stack[i])) {
            return true;
        }
    }
    return false;
}

static inline void push(int *stack, int row, int col)
{
    stack[row] = col;
}

static inline int pop(int *stack, int row)
{
    int col = stack[row];
    stack[row] = -1;
    return col;
}

static inline int top(int *stack, int n)
{
    int row;
    for (row = n - 1; row >= 0; row--) {
        if (stack[row] != -1) {
            return row;
        }
    }
    return 0;
}

static void dfs(int n, int row, int *stack, int *count)
{
    int col;
    if (row == n) {
        (*count)++;
    } else {
        for (col = 0; col < n; col++) {
            if (row == 0 || !conflict(stack, row, col)) {
                stack[row] = col;
                dfs(n, row + 1, stack, count);
            }
        }
    }
}

int totalNQueens(int n) {
#if 1
    int count = 0;
    int *stack = malloc(n * sizeof(int));
    dfs(n, 0, stack, &count);
    return count;
#else
    int row = 0, col = 0, sum = 0, cap = 1;
    int *stack = malloc(n * sizeof(int));
    for (row = 0; row < n; row++) {
        stack[row] = -1;
    }

    if (n == 1) {
        return 1;
    }

    for (; ;) {
        for (; row < n; row++) {
            while (col < n) {
                if (conflict(stack, row, col)) {
                    while (col == n - 1) {
                        /* No other positions in this row and therefore backtracking */
                        if (--row < 0) {
                            /* All solution provided */
                            free(stack);
                            return sum;
                        }
                        col = pop(stack, row);
                    }
                    col++;
                } else {
                    push(stack, row, col);
                    break;
                }
            }
            col = 0;
        }

        /* Full stack, a new complete solution */
        row = top(stack, n);
        if (row == n - 1) {
            sum++;
        }

        /* Move on to find if there are still other solutions */
        col = pop(stack, row);
        col++;
    }    
#endif
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./queen 8\n");
        exit(-1);
    }

    int n = atoi(argv[1]);
    printf("Total %d solution for %d queens.\n", totalNQueens(n), n);
    return 0;
}
