#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool valid(char *ip, int len)
{
    if (len > 1 && ip[0] == '0') {
        return false;
    }
    if (len == 3) {
        int n = (ip[0] - '0') * 100 + (ip[1] - '0') * 10 + (ip[2] - '0');
        if (n > 255) {
            return false;
        }
    }
    return true;
}

#define WIDTH 4

static void dfs(char *s, int start, char *stack, int num, char **results, int *count)
{
    int i, j;
    if (num == 4) {
        if (s[start] == '\0') {
            results[*count] = malloc(3 * 4 + 3 + 1);
            char *p = results[*count];
            for (j = 0; j < num; j++) {
                char *q = stack + j * WIDTH;
                while ((*p++ = *q++) != '\0') {}
                if (j != 3) {
                    *(p - 1) = '.';
                }
            }
            (*count)++;
        }
    } else {
        char *p = stack + num * WIDTH;
        char *q = p;
        /* start + 3 indicates each ip number should not exceed size of 3 */
        for (i = start; s[i] != '\0' && i < start + 3; i++) {
            *q++ = s[i];
            *q = '\0';
            if (!valid(p, q - p)) {
                return;
            }
            dfs(s, i + 1, stack, num + 1, results, count);
            if (num + 1 < 4) {
                memset(stack + (num + 1) * WIDTH, 0, WIDTH);
            }
        }
    }
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static char** restoreIpAddresses(char* s, int* returnSize)
{
    int count = 0;
    char **results = malloc(100 * sizeof(char *));
    char addr[16] = { '\0' };
    dfs(s, 0, addr, 0, results, &count);
    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test num\n");
        exit(-1);
    }

    int i, count = 0;
    char **list = restoreIpAddresses(argv[1], &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }
}
