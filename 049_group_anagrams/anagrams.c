#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

static inline void INIT_HLIST_HEAD(struct hlist_head *h) {
    h->first = NULL;
}

static inline int hlist_empty(struct hlist_head *h) {
    return !h->first;
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first != NULL) {
        h->first->pprev = &n->next;
    }
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

struct word_node {
    struct hlist_node node;
    int index;
};

struct word_hash {
    struct hlist_head head;
    char *word;
    int num;
};

static void insert_sort(char *s, int len)
{
    int i, j;
    for (i = 1; i < len; i++) {
        char tmp = s[i];
        j = i - 1;
        for (; j >= 0 && s[j] > tmp; j--) {
            s[j + 1] = s[j];
        }
        s[j + 1] = tmp;
    }
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
static char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize) {
    int i, j, count = 0;
    struct word_node *wn;

    int hash_size = strsSize;
    struct word_hash *ht = malloc(hash_size * sizeof(*ht));
    for (i = 0; i < hash_size; i++) {
        INIT_HLIST_HEAD(&ht[i].head);
        ht[i].num = 0;
    }

    char **words = malloc(strsSize * sizeof(char *));
    for (i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        words[i] = malloc(len + 1);
        strcpy(words[i], strs[i]);
        insert_sort(words[i], len);
        int hash = BKDRHash(words[i], hash_size);
        /* find available hash bucket */
        for (j = hash; ht[j].num > 0 && strcmp(ht[j].word, words[i]); j = ++j % hash_size) {}
        wn = malloc(sizeof(*wn));
        wn->index = i;
        if (ht[j].num == 0) {
            ht[j].word = words[i];
            count++;
        }
        hlist_add_head(&wn->node, &ht[j].head);
        ht[j].num++;
    }

    j = 0;
    struct hlist_node *p;
    char ***lists = malloc(count * sizeof(char **));
    *columnSizes = malloc(count * sizeof(int));
    for (i = 0; i < hash_size; i++) {
        if (ht[i].num > 0) {
            (*columnSizes)[j] = ht[i].num;
            lists[j] = malloc(ht[i].num * sizeof(char *));
            int k = 0;
            hlist_for_each(p, &ht[i].head) {
                wn = list_entry(p, struct word_node, node);
                lists[j][k++] = strs[wn->index];
            }
            j++;
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
