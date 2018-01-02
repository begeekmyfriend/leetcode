#include <stdio.h>
#include <stdlib.h>

static int longestValidParentheses(char* s)
{
    int cap = 8000, error = -1;
    int length = 0, max_length = 0;
    char *p = s;
    int *stack = malloc(cap * sizeof(int));
    int *top = stack;

    while (*p != '\0') {
        if (*p == '(') {
            if (top + 1 - stack >= cap) {
                cap *= 2;
                stack = realloc(stack, cap * sizeof(int));
            }
            *top++ = p - s;
        } else {
            if (top > stack) {
                if (--top == stack) {
                    /* The stack never keep ')' so we use 'error' to record index */
                    length = p - (s + error);
                } else {
                    /* The *(top - 1) is the index of the last kept '(' */
                    length = p - (s + *(top - 1));
                }
                if (length > max_length) {
                    max_length = length;
                }
            } else {
                error = p - s;
            }
        }
        p++;
    }
    return max_length;
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
