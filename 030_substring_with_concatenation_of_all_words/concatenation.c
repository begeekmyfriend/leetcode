#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uthash.h"

struct word_hash {
    char *word;
    int freq;
    int index;
    UT_hash_handle hh;
};

static struct word_hash *hash_table = NULL;

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    if (s == NULL || wordsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int i, index, cap = 1, count = 0;
    char *start = s;
    struct word_hash *obj, *tmp;
    int len = strlen(words[0]);
    char *word = malloc(len + 1);
    int length = strlen(s) - wordsSize * len + 1;
    int *freqs = malloc(wordsSize * sizeof(int));
    int *sub_indexes = malloc(cap * sizeof(int));

    word[len] = '\0';
    for (i = 0; i < wordsSize; i++) {
        HASH_FIND_STR(hash_table, words[i], obj);
        if (obj == NULL) {
            obj = malloc(sizeof(*obj));
            obj->word = words[i];
            obj->freq = 1;
            obj->index = i;
            HASH_ADD_STR(hash_table, word, obj);
        } else {
            obj->freq++;
        }
    }

    while (length-- > 0) {
        int sum = 0;
        memset(freqs, 0, wordsSize * sizeof(int));
        for (i = 0; i < wordsSize; i++) {
            memcpy(word, s + i * len, len);
            HASH_FIND_STR(hash_table, word, obj);
            if (obj == NULL) {
                break;
            } else {
                sum += ++freqs[obj->index] <= obj->freq ? 1 : -1;
            }
        }
        if (sum == wordsSize && i == wordsSize) {
            if (count + 1 >= cap) {
                cap *= 2;
                sub_indexes = realloc(sub_indexes, cap * sizeof(int));
            }
            sub_indexes[count++] = s - start;
        }
        s++;
    }

    HASH_ITER(hh, hash_table, obj, tmp) {
        HASH_DEL(hash_table, obj);
        free(obj);
    }

    *returnSize = count;
    return sub_indexes;
}

int main(int argc, char **argv)
{
    int i, count;
    int *indexes = findSubstring(argv[1], argv + 2, argc - 2, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", indexes[i]);
    }
    printf("\n");
    return 0;
}
