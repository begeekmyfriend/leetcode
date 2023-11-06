#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int lengthOfLongestSubstring(char *s)
{
    int count[256] = {0};
    int len = 0;
    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        count[s[i]]++;
        while (count[s[i]] > 1) {
            len = i - j > len ? i - j : len;
            count[s[j++]] -= 1;
        }
    }

    return i - j > len ? i - j : len;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }

    printf("%d\n", lengthOfLongestSubstring(argv[1]));
    return 0;
}
