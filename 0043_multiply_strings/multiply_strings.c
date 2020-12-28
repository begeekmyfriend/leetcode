#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char* multiply(char* num1, char* num2)
{
    if (*num1 == '\0') {
        return num1;
    }

    if (*num2 == '\0') {
        return num2;
    }

    int i, j;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char *result = malloc(len1 + len2 + 1);
    memset(result, '0', len1 + len2 + 1);
    result[len1 + len2] = '\0';

    for (i = len2 - 1; i >= 0; i--) {
        int carry = 0;
        for (j = len1 - 1; j >= 0; j--) {
            carry += (num2[i] - '0') * (num1[j] - '0') + (result[i + j + 1] - '0');
            result[i + j + 1] = carry % 10 + '0';
            carry /= 10;
        }
        result[i + j + 1] = carry + '0';
    }

    while (result[0] == '0' && result[1] != '\0') {
        result++;
    }

    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test m1 m2\n");
        exit(-1);
    }
    printf("%s\n", multiply(argv[1], argv[2]));
    return 0;
}
