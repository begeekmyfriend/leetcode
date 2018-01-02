#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_hash {
    char *word;
    int num;
    int indexes[10];
};

static int compare(const void *a, const void *b)
{
    return *(char *) a - *(char *) b;
}

static inline int BKDRHash(char *s, size_t size)
{
    int seed = 31; /* 131 1313 13131... */
    unsigned long hash = 0;
    while (*s != '\0') {
        hash = hash * seed + *s++;
    }
    return hash % size;
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize)
{
    int i, j, count = 0;
    int hash_size = strsSize;
    struct word_hash *ht = calloc(hash_size, sizeof(*ht));

    char **words = malloc(strsSize * sizeof(char *));
    for (i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        words[i] = malloc(len + 1);
        strcpy(words[i], strs[i]);
        qsort(words[i], len, sizeof(char), compare);
        int hash = BKDRHash(words[i], hash_size);
        /* find available hash bucket */
        for (j = hash; ht[j].num > 0 && strcmp(ht[j].word, words[i]); j = ++j % hash_size) {}
        if (ht[j].num == 0) {
            ht[j].word = words[i];
            count++;
        }
        ht[j].indexes[ht[j].num++] = i;
    }

    int k = 0;
    struct hlist_node *p;
    char ***lists = malloc(count * sizeof(char **));
    *columnSizes = malloc(count * sizeof(int));
    for (i = 0; i < hash_size; i++) {
        if (ht[i].num > 0) {
            (*columnSizes)[k] = ht[i].num;
            lists[k] = malloc(ht[i].num * sizeof(char *));
            for (j = 0; j < ht[i].num; j++) {
                int index = ht[i].indexes[j];
                lists[k][j] = strs[index];
            }
            k++;
        }
    }

    *returnSize = count;
    return lists;
}

int main(int argc, char **argv)
{
    int *column_sizes, count = 0, i, j;
    char ***lists = groupAnagrams(argv + 1, argc - 1, &column_sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < column_sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
