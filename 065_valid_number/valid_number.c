#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

static bool isNumber(const char *s)
{
    while (*s == ' ')
        ++s;
    bool if_find_num = false;
    if (*s == '-' || *s == '+')
        ++s;
    while (isdigit(*s)) {
        if_find_num = true;
        ++s;
    }
    if (*s == '.')
        ++s;
    while (isdigit(*s)) {
        if_find_num = true;
        ++s;
    }
    if (if_find_num == true && *s == 'e') {
        ++s;
        if (*s == '+' || *s == '-')
            ++s;
        if_find_num = false;
        while (isdigit(*s)) {
            if_find_num = true;
            ++s;
        }
    }
    while (*s == ' ')
        ++s;
    return *s == '\0' && if_find_num == true;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }
    printf("%s\n", isNumber(argv[1]) ? "true" : "false");
    return 0;
}
