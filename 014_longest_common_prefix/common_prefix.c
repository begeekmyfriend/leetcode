#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char* longestCommonPrefix(char** strs, int strsSize)
{
    int i, capacity = 50, count = 0;
    char *result = malloc(50);
    bool go_on = true;
    while (strsSize > 0 && go_on) {
        char temp = strs[0][count];
        for (i = 1; i < strsSize; i++) {
            if (temp != strs[i][count]) break;
        }
        if (i == strsSize && temp != '\0') {
            if (count + 1 + 1 >= capacity) {
                capacity *= 2;
                result = realloc(result, capacity + 1);
            }
            result[count++] = temp;
        } else {
            go_on = false;
        }
    }
    result[count++] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    printf("%s\n", longestCommonPrefix(argv + 1, argc - 1));
    return 0;
}
