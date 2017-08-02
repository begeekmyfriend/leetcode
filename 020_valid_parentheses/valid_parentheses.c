#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isValid(char *s)
{
    int n = 0, cap = 100;
    char *stack = malloc(cap);

    while (*s != '\0') {
        switch(*s) {
        case '(':
        case '[':
        case '{':
            if (n + 1 >= cap) {
                cap *= 2;
                stack = realloc(stack, cap);
            }
            stack[n++] = *s;
            break;
        case ')':
            if (stack[--n] != '(') return false;
            break;
        case ']':
            if (stack[--n] != '[') return false;
            break;
        case '}':
            if (stack[--n] != '{') return false;
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
