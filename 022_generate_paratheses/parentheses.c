#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static char** generateParenthesis(int n, int* returnSize)
{
    int left, right, cap = 5000, count = 0;
    char *stack = malloc(2 * n + 1);
    char **parentheses = malloc(cap * sizeof(char *));

    char *p = stack;
    left = right = 0;
    stack[2 * n] = '\0';

    /* begin and end condition of loop */
    while (p != stack || count == 0) {
        if (left == n && right == n) {
            parentheses[count] = malloc(2 * n + 1);
            strcpy(parentheses[count], stack);
            count++;

            /* back tracking */
            while (--p != stack) {
                if (*p == '(') {
                    /* until ')' is no more than '(' is guaranteed */
                    if (--left > right) {
                        *p++ = ')';
                        right++;
                        break;
                    }
                } else {
                    right--;
                }
            }
        } else {
            /* forward */
            while (left < n) {
                *p++ = '(';
                left++;
            }
            while (right < n) {
                *p++ = ')';
                right++;
            }
        }
    }

    *returnSize = count;
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
