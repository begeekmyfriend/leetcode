#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


static int dfs(char **input)
{
    int i, res = 0;
    int num = 0;
    int stk[700], pos = 0;
    char sign = '+';
    char *s = *input;

    while (*s != '\0') {
        char c = *s++;
        if (isdigit(c)) {
            num = 10 * num + (c - '0');
        }

        if (c == '(') {
            /* dfs("2*(1+3)") = 2 * dfs("1+3") */
            num = dfs(&s);
        }

        if (!isdigit(c) && c != ' ' || *s == '\0') {
            switch (sign) {
                case '+':
                    stk[pos++] = num;
                    break;
                case '-':
                    stk[pos++] = -num;
                    break;
                case '*':
                    stk[pos - 1] *= num;
                    break;
                case '/':
                    stk[pos - 1] /= num;
                    break;
            }
            /* update the sign and reset the number */
            sign = c;
            num = 0;
        }

        /* return from the dfs */
        if (c == ')')
            break;
    }

    /* update position */
    *input = s;

    while (pos > 0) {
        res += stk[--pos];
    }

    return res;
}

static int calculator(char *s)
{
    return dfs(&s);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%d\n", calculator(argv[1]));
    return 0;
}
