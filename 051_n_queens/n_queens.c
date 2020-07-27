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

static char **solute(int *stack, int n)
{
    int row, col;
    char **solution = malloc(n * sizeof(char *));
    for (row = 0; row < n; row++) {
        char *line = malloc(n + 1);
        for (col = 0; col < n; col++) {
            line[col] = col == stack[row] ? 'Q' : '.';
        }
        line[n] = '\0';
        solution[row] = line;
    }
    return solution;
}

static void dfs(int n, int row, int *stack, char ***solutions, int *count, int *col_sizes)
{
    int col;
    if (row == n) {
        solutions[*count] = solute(stack, n);
        col_sizes[*count] = n;
        (*count)++;
    } else {
        for (col = 0; col < n; col++) {
            if (row == 0 || !conflict(stack, row, col)) {
                stack[row] = col;
                dfs(n, row + 1, stack, solutions, count, col_sizes);
            }
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
    int row = 0, col = 0, sum = 0;
    char ***solutions = malloc(1000 * sizeof(char **));
    *returnColumnSizes = malloc(1000 * sizeof(int));
    int *stack = malloc(n * sizeof(int));

#if 1
    *returnSize = 0;
    dfs(n, 0, stack, solutions, returnSize, *returnColumnSizes);
    return solutions;
#else
    for (row = 0; row < n; row++) {
        stack[row] = -1;
    }

    if (n == 1) {
        stack[0] = 0;
        solutions[0] = solute(stack, n);
        *returnSize = 1;
        *returnColumnSizes[0] = 1;
        return solutions;
    }

    for (; ;) {
        for (; row < n; row++) {
            while (col < n) {
                if (conflict(stack, row, col)) {
                    while (col == n - 1) {
                        /* No other positions in this row and therefore backtracking */
                        if (--row < 0) {
                            /* All solution provided */
                            *returnSize = sum;
                            return solutions;
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
            solutions[sum] = solute(stack, n);
            (*returnColumnSizes)[sum] = n;
            sum++;
        }

        /* Move on to find if there are still other solutions */
        col = pop(stack, row);
        col++;
    }

    assert(0);
#endif
}

int main(int argc, char **argv)
{
    int i, n, row, col, num_of_solution;

    if (argc != 2) {
        printf("Usage: ./queen 8\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    int *col_sizes;
    char ***solutions = solveNQueens(n, &num_of_solution, &col_sizes);
    for (i = 0; i < num_of_solution; i++) {
        char **solution = solutions[i];
        for (row = 0; row < n; row++) {
            char *line = solution[row];
            for (col = 0; col < n; col++) {
                putchar(line[col]);
            }
            putchar('\n');
        }
        printf("The %dth solution.\n", i + 1);
    }

    return 0;
}
