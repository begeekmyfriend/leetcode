#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dfs(int n, int left, int right, char *stack, int len, char **results, int *count)
{
    if (len == 2 * n) {
        results[*count] = malloc((len + 1) * sizeof(char));
        strcpy(results[(*count)++], stack);
        return;
    }

    if (left < n) {
        stack[len] = '(';
        dfs(n, left + 1, right, stack, len + 1, results, count);
    }

    if (right < left) {
        stack[len] = ')';
        dfs(n, left, right + 1, stack, len + 1, results, count);
    }
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static char** generateParenthesis(int n, int* returnSize)
{
    char *stack = calloc(2 * n + 1, sizeof(char));
    char **parentheses = malloc(5000 * sizeof(char *));
    *returnSize = 0;
    dfs(n, 0, 0, stack, 0, parentheses, returnSize);

    return parentheses;
}

int main(int argc, char **argv)
{
    int i, count;
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test 3\n");
        exit(-1);
    }
    char ** lists = generateParenthesis(atoi(argv[1]), &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", lists[i]);
    }
    return 0;
}
