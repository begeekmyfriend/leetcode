#include <stdio.h>
#include <stdlib.h>


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
                    /* distancd of the latest ')' */
                    len = i - invalid;
                } else {
                    /* distance of the remote '(' */
                    len = i - *(top - 1);
                }
                if (len > max_len) {
                    max_len = len;
                }
            } else {
                /* record the index of last ')' but no push */
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
