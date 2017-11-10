#include <stdio.h>
#include <stdlib.h>

static int a2i(char *s)
{
    int n = 0;
    int sign = 0;
    while (*s != '\0') {
        switch (s[0]) {
        case '+':
            break;
        case '-':
            sign = 1;
            break;
        case '*':
            break;
        case '/':
            break;
        default:
            n = n * 10 + (s[0] - '0');
            break;
        }
        s++;
    }
    return sign ? -n : n;
}

static int evalRPN(char **tokens, int tokensSize)
{
    int i, res, a, b;
    int stack[500], len = 0;

    for (i = 0; i < tokensSize; i++) {
        switch (tokens[i][0]) {
        case '\0':
            break;
        case '+':
            if (len > 0) {
                b = stack[--len];
            }
            if (len > 0) {
                a = stack[--len];
                stack[len++] = a + b;
            }
            break;
        case '*':
            if (len > 0) {
                b = stack[--len];
            }
            if (len > 0) {
                a = stack[--len];
                stack[len++] = a * b;
            }
            break;
        case '/':
            if (len > 0) {
                b = stack[--len];
            }
            if (len > 0) {
                a = stack[--len];
                stack[len++] = a / b;
            }
            break;
        case '-':
            if (tokens[i][1] == '\0') {
                if (len > 0) {
                    b = stack[--len];
                }
                if (len > 0) {
                    a = stack[--len];
                    stack[len++] = a - b;
                }
                break;
            }
        default:
            stack[len++] = a2i(tokens[i]);
        }
    }

    return len > 0 ? stack[len - 1] : 0;
}

int main(int argc, char **argv)
{
    printf("%d\n", evalRPN(argv + 1, argc - 1));
    return 0;
}
