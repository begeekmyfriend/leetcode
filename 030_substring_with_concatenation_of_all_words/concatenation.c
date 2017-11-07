#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct word_hash {
    char *word;
    int freq;
};

static inline int BKDRHash(char *s, size_t size)
{
    int seed = 31; /* 131 1313 13131... */
    unsigned long hash = 0;
    while (*s != '\0') {
        hash = hash * seed + *s++;
    }
    return hash % size;
}

static int find(char *word, struct word_hash *table, int size)
{
    int hash = BKDRHash(word, size);
    int i = hash;
    do {
        if (table[i].freq > 0 && !strcmp(table[i].word, word)) {
            return i;
        }
        i = ++i % size;
    } while (i != hash);
    return -1;
}

static void add(char *word, struct word_hash *table, int size)
{
    int i, hash = BKDRHash(word, size);
    for (i = hash; table[i].freq > 0 && strcmp(table[i].word, word); i = ++i % size) {}
        if (table[i].freq == 0) {
            table[i].word = word;
        }
        table[i].freq++;
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int *findSubstring(char *s, char **words, int wordsSize, int *returnSize)
{
    if (*s == '\0' || wordsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int i, j, cap = 500, count = 0;
    char *start = s;
    struct word_node *wn;
    int hash_size = wordsSize * 2;
    int len = strlen(words[0]);
    char *word = malloc(len + 1);
    int *indexes = malloc(cap * sizeof(int));
    int *freqs = malloc(wordsSize * sizeof(int));
    struct word_hash *table = malloc(hash_size * sizeof(*table));

    memset(table, 0, hash_size * sizeof(*table));
    for (i = 0; i < wordsSize; i++) {
        add(words[i], table, hash_size);
    }

    word[len] = '\0';
    int length = len * wordsSize - 1;
    while (s[length] != '\0') {
        memset(freqs, 0, hash_size * sizeof(int));
        for (i = 0; i < wordsSize; i++) {
            memcpy(word, s + i * len, len);
            int index = find(word, table, hash_size);
            if (index < 0) {
                break;
            } else {
                if (++freqs[index] > table[index].freq) {
                    break;
                }
            }
        }

        if (i == wordsSize) {
            indexes[count++] = s - start;
        }
        s++;
    }

    *returnSize = count;
    return indexes;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test str w1 w2...\n");
        exit(-1);
    }

    int i, count = 0;
    int *indexes = findSubstring(argv[1], argv + 2, argc - 2, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", indexes[i]);
    }
    printf("\n");
    return 0;
}
