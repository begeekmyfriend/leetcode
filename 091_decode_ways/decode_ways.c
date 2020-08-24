#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int numDecodings(char* s)
{
    int len = strlen(s);
    if (len == 0) {
        return 0;
    }

    int a = 1;
    int b = s[0] == '0' ? 0 : a;
    int c = b;
    /* DP: How many counts in sequence c = f(a, b) and c counts s[i - 1] */
    for (int i = 2; i <= len; i++) {
        c = s[i - 1] == '0' ? 0 : b;
        int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (num >= 10 && num <= 26) {
            c += a;
        }
        a = b;
        b = c;
    }

    return c;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }
    printf("%d\n", numDecodings(argv[1]));
    return 0;
}
