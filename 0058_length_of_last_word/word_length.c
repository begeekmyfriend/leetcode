#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLastWord(char *s)
{
    int word_len = 0;
    int len = strlen(s);

    while (len > 0 && s[--len] == ' ') {}

    while (len >= 0 && s[len] != ' ') {
        word_len++;
        len--;
    }

    return word_len;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test word\n");
        exit(-1);
    }

    printf("%d\n", lengthOfLastWord(argv[1]));
    return 0;
}
