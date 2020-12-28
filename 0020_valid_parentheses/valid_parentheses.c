#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isValid(char *s)
{
    int n = 0;
    char stack[100];

    while (*s != '\0') {
        switch(*s) {
        case '(':
        case '[':
        case '{':
            stack[n++] = *s;
            break;
        case ')':
            if (n == 0 || stack[--n] != '(') return false;
            break;
        case ']':
            if (n == 0 || stack[--n] != '[') return false;
            break;
        case '}':
            if (n == 0 || stack[--n] != '{') return false;
            break;
        default:
            return false;
        }
        s++;
    }

    return n == 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test xxxx");
        exit(-1);
    }
    printf("%s\n", isValid(argv[1]) ? "true" : "false");
    return 0;
}
