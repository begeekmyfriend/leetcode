/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv)
{
        char *alpha, *s;
        int n = 0, sign = 0;

        if (argc != 2) {
                printf("Usage: ./atoi 123\n");
                exit(-1);
        }

        alpha = argv[1];
        while (*alpha == ' ' || *alpha == '\t') {
                alpha++;
        }

        for (s = alpha; *s != '\0'; s++) {
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
                } else if (*s == '-' && isdigit(*(s + 1))) {
                        sign = 1;
                } else if (*s == '+' && isdigit(*(s + 1))) {
                        sign = 0;
                } else {
                        break;
                }
        }

        n = sign ? -n : n;
        printf("n = %d %x\n", n, n);

        return 0;
}
