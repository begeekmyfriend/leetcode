#include <stdio.h>
#include <stdlib.h>

static int calculator(char *s)
{
    int n;
    int pos1 = 0;
    int pos2 = 0;
    int *nums = malloc(1000 * sizeof(int));
    char *signs = malloc(1000 * sizeof(char));

    nums[pos1++] = 0;
    while (*s != '\0') {
        switch (*s) {
        case '+':
        case '-':
        case '(':
            signs[pos2++] = *s;
            break;
        case ')':
            --pos2;
            if (pos1 >= 2 && pos2 > 0 && signs[pos2 - 1] != '(') {
                n = nums[--pos1];
                int a = nums[--pos1];
                if (signs[--pos2] == '+') {
                    n = a + n;
                } else {
                    n = a - n;
                }
            }
            nums[pos1++] = n;
            break;
        case ' ':
            break;
        default:
            n = 0;
            while(*s >= '0' && *s <= '9') {
                n = n * 10 + (*s - '0');
                s++;
            }
            s--;

            if (pos1 >= 2 && signs[pos2 - 1] != '(' && signs[pos2 - 1] != '(') {
                int a = nums[--pos1];
                if (signs[--pos2] == '+') {
                    n = a + n;
                } else {
                    n = a - n;
                }
            }
            nums[pos1++] = n;
            break;
        }
        s++;
    }

    return n;
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
