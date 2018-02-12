#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* convert(char* s, int numRows)
{
    if (numRows <= 1) return s;

    int len = strlen(s);
    char *new_str = malloc(len + 1);    
    char *p = new_str;
    int row = 0;
    for (row = 0; row < numRows; row++) {
        int interval1 = numRows + (numRows - 2) - row * 2;
        int interval2 = 2 * row;
        int flag = 0;
        int i = row;
        while (i < len) {
            *p++ = s[i];
            int delta = 0;
            do {
                delta = flag == 0 ? interval1 : interval2;
                flag = !flag;
            } while (delta == 0);
            i += delta;
        }
    }

    new_str[len] = '\0';
    return new_str;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "./test string num\n");
        exit(-1);
    }

    printf("%s\n", convert(argv[1], atoi(argv[2])));
    return 0;
}
