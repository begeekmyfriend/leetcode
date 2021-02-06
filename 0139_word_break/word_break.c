#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static int dfs(char *s, char **words, int *lens, int size, bool *ends, int index)
{   
    int i, j;
    if (*s == '\0') {
        return true;
    } else if (!ends[index]) {
        return false;
    } else {
        for (i = 0; i < size; i++) {
            ends[index] = false;
            if (!strncmp(s, words[i], lens[i])) {
                /* post-order traverse */
                bool ok = dfs(s + lens[i], words, lens, size, ends, index + lens[i]);
                if (ok) {
                    /* string s all matched */
                    return true;
                }
            }
        }

        return ends[index];
    }
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    if (wordDictSize == 0) {
        return false;
    }

    int i, len = strlen(s);
    int *lens = malloc(wordDictSize * sizeof(int));
    for (i = 0; i < wordDictSize; i++) {
        lens[i] = strlen(wordDict[i]);
    }

    bool *ends = malloc(len);
    memset(ends, true, len);
    return dfs(s, wordDict, lens, wordDictSize, ends, 0);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test word dictionary...\n");
        exit(-1);
    }

    printf("%s\n", wordBreak(argv[1], argv + 2, argc - 2) ? "true" : "false");
    return 0;
}
