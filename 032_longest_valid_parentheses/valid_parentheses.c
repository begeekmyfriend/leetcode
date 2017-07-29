#include <stdio.h>
#include <stdlib.h>

static int longestValidParentheses(char* s) {
    int cap = 1, error = -1;
    int length = 0, max_length = 0;
    char *p = s;
    int *stack = malloc(cap * sizeof(int));
    int *top = stack;

    while (*s != '\0') {
        if (*s == '(') {
            if (top + 1 - stack >= cap) {
                cap *= 2;
                stack = realloc(stack, cap * sizeof(int));
            }
            *top++ = s - p;
        } else {
            if (top > stack) {
                if (--top == stack) {
                    /* The stack never keep ')' so we use 'error' to record index */
                    length = s - p - error;
                } else {
                    /* The *(top - 1) is the index of the last kept '(' */
                    length = s - p - *(top - 1);
                }
                if (length > max_length) {
                    max_length = length;
                }
            } else {
                error = s - p;
            }
        }
        s++;
    }
    return max_length;
}

int main(int argc, char **argv)
{
    printf("%d\n", longestValidParentheses(argv[1]));
    return 0;
}
