/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int N;

static inline int conflict(int *stack, int i, int j)
{
    int k;
    for (k = 0; k < i; k++) {
        if (j == stack[k] || abs(i - k) == abs(j - stack[k])) {
            return 1;
        }
    }
    
    return 0;
}

static inline void push(int *stack, int i, int j)
{
    stack[i] = j;
    // printf("push %d %d\n", i, j);
}

static inline int pop(int *stack, int i)
{
    int j = stack[i];
    stack[i] = -1;
    // printf("pop %d %d\n", i, j);
    return j;
}

static inline int top(int *stack)
{
    int i;
    for (i = N - 1; i >= 0; i--) {
        if (stack[i] != -1) {
            return i;
        }
    }

    return 0;
}

void show(int *stack)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j == stack[i]) {
                printf("Q");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    int i, j, sum = 0;
    int *stack;

    if (argc != 2) {
        printf("Usage: ./queen 8\n");
        exit(-1);
    }

    N = atoi(argv[1]);
    if (N <= 0) {
        exit(0);
    }

    stack = malloc(N * sizeof(*stack));
    if (stack == NULL) {
        exit(-1);
    }

    if (N == 1) {
        stack[0] = 0;
        show(stack);
        printf("This is the %dth solution.\n", ++sum);
        exit(0);
    }

    for (i = 0; i < N; i++) {
        stack[i] = -1;
    }

    i = j = 0;
    for (; ;) {
        for (; i < N; i++) {
            while (j < N) {
                if (conflict(stack, i, j)) {
                    while (j == N - 1) {
                        /* No space for row[i] so backtracking is needed */
                        if (--i < 0) {
                            free(stack);
                            exit(0);
                        }
                        j = pop(stack, i);
                    }
                    j++;
                } else {
                    push(stack, i, j);
                    break;
                }
            }
            j = 0;
        }

        i = top(stack);
        if (i == N - 1) {
            show(stack);
            printf("This is the %dth solution.\n", ++sum);
        }

        j = pop(stack, i);
        j++;
    }

    assert(0);
    return 0;
}
