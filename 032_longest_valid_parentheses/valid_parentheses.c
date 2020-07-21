#include <stdio.h>
#include <stdlib.h>


static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int longestValidParentheses(char* s)
{
    int i, cap = 18000, invalid = -1;
    int len = 0, max_len = 0;
    int *stack = malloc(cap * sizeof(int));
    int *top = stack;

    /* We only restore index of '(' since restrain of space */
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            *top++ = i;
        } else {
            if (top > stack) {
                if (--top == stack) {
                    /* locate the remote ')' */
                    max_len = max(i - invalid, max_len);
                } else {
                    /* locate the remote '(' */
                    max_len = max(i - *(top - 1), max_len);
                }
            } else {
                /* record the index of the remote ')' and no push */
                invalid = i;
            }
        }
    }
    return max_len;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test parathesis\n");
        exit(-1);
    }

    printf("%d\n", longestValidParentheses(argv[1]));
    return 0;
}
