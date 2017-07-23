#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uthash.h"

struct str_hash {
    char *str;
    int *indexes;
    int freq;
    int cap;
    UT_hash_handle hh;
};

static struct str_hash *hash_table = NULL;

static void insert_sort(char *s, int len)
{
    long i, j;
    for (i = 1; i < len; i++) {
        char tmp = s[i];
        j = i - 1;
        for (; j >= 0 && s[j] > tmp; j--) {
            s[j + 1] = s[j];
        }
        s[j + 1] = tmp;
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize) {
    int i, j, count = 0;
    struct str_hash *obj, *tmp;
    char **words = malloc(strsSize * sizeof(char *));

    for (i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        words[i] = malloc(len + 1);
        strcpy(words[i], strs[i]);
        insert_sort(words[i], len);
        HASH_FIND_STR(hash_table, words[i], obj);
        if (obj == NULL) {
            obj = malloc(sizeof(*obj));
            obj->str = words[i];
            obj->freq = 1;
            obj->cap = 1;
            obj->indexes = malloc(sizeof(int));
            obj->indexes[0] = i;
            HASH_ADD_STR(hash_table, str, obj);
            count++;
        } else {
            if (obj->freq + 1 >= obj->cap) {
                obj->cap *= 2;
                obj->indexes = realloc(obj->indexes, obj->cap * sizeof(int));
            }
            obj->indexes[obj->freq++] = i;
        }
    }

    char ***ret_lists = malloc(count * sizeof(char **));
    int *column_sizes = malloc(count * sizeof(int));

    i = 0;
    HASH_ITER(hh, hash_table, obj, tmp) {
        ret_lists[i] = malloc(obj->freq * sizeof(char *));
        column_sizes[i] = obj->freq;
        for (j = 0; j < column_sizes[i]; j++) {
            ret_lists[i][j] = strs[obj->indexes[j]];
        }
        HASH_DEL(hash_table, obj);
        free(obj);
        i++;
    }

    *columnSizes = column_sizes;
    *returnSize = count;
    return ret_lists;
}

int main(int argc, char **argv)
{
    int *column_sizes, count, i, j;
    char ***lists = groupAnagrams(argv + 1, argc - 1, &column_sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < column_sizes[i]; j++) {
            printf("%s\n", lists[i][j]);
        }
    }
    return 0;
}
