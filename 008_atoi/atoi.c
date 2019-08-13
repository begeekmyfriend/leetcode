#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int myAtoi(char* str)
{
    char *s;
    int n = 0, sign = 0;

    while (*str == ' ' || *str == '\t') {
        str++;
    }

    for (s = str; *s != '\0'; s++) {
        if (isdigit(*s)) {
            int d = *s - '0';
            if (sign) {
                if (-n < (INT_MIN + d) / 10) {
                    n = INT_MIN;
                    break;
                }
            } else {
                if (n > (INT_MAX - d) / 10) {
                    n = INT_MAX;
                    break;
                }
            }
            n = n * 10 + d;
        } else if (*s == '-' && isdigit(*(s + 1)) && (n == 0)) {
            sign = 1;
        } else if (*s == '+' && isdigit(*(s + 1)) && (n == 0)) {
            sign = 0;
        } else {
            break;
        }
    }

    return sign ? -n : n;   
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./atoi 123\n");
        exit(-1);
    }

    int n = myAtoi(argv[1]);
    printf("n = %d %x\n", n, n);

    return 0;
}
