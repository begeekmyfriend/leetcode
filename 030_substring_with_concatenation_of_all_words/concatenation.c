#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

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

struct word_node {
    struct hlist_node node;
    char *word;
    int index;
};

static inline int BKDRHash(char *s, size_t size)
{
    int seed = 131; /* 131 1313 13131... */
    unsigned long hash = 0;
    while (*s != '\0') {
        hash = hash * seed + *s++;
    }
    return hash % size;
}

static int find(char *word, struct hlist_head *heads, int size)
{
    int hash = BKDRHash(word, size);
    struct hlist_node *pos;
    hlist_for_each(pos, &heads[hash]) {
        struct word_node *wn = list_entry(pos, struct word_node, node);
        if (!strcmp(wn->word, word)) {
            return wn->index;
        }
    }
    return -1;
}

static void add(char **words, int index, struct hlist_head *heads, int size, int *freqs)
{
    int hash = BKDRHash(words[index], size);
    struct hlist_node *pos;
    struct word_node *wn;
    hlist_for_each(pos, &heads[hash]) {
        wn = list_entry(pos, struct word_node, node);
        if (!strcmp(wn->word, words[index])) {
            freqs[wn->index]++;
            return;
        }
    }
    wn = malloc(sizeof(*wn));
    wn->word = words[index];
    wn->index = index;
    hlist_add_head(&wn->node, &heads[hash]);
    freqs[wn->index]++;
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

    int i, j, cap = 10000, count = 0;
    int hash_size = wordsSize;
    struct hlist_head *heads = malloc(hash_size * sizeof(*heads));
    for (i = 0; i < hash_size; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    int *freqs = malloc(wordsSize * sizeof(int));
    memset(freqs, 0, wordsSize * sizeof(int));

    for (i = 0; i < wordsSize; i++) {
        add(words, i, heads, hash_size, freqs);
    }

    int len = strlen(words[0]);
    int length = len * wordsSize - 1;
    char *word = malloc(len + 1);
    word[len] = '\0';
    int *indexes = malloc(cap * sizeof(int));
    for (i = 0; s[i] != '\0'; i++) {
        memcpy(word, s + i, len);
        indexes[i] = find(word, heads, hash_size);
    }

    int *results = malloc(cap * sizeof(int));
    int *fqs = malloc(wordsSize * sizeof(int));
    for (i = 0; s[i + length] != '\0'; i++) {
        memset(fqs, 0, wordsSize * sizeof(int));
        for (j = 0; j < wordsSize; j++) {
            int index = indexes[i + j * len];
            if (index < 0 || ++fqs[index] > freqs[index]) {
                break;
            }
        }
        if (j == wordsSize) {
            results[count++] = i;
        }
    }

    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test str w1 w2...\n");
        exit(-1);
    }

    int i, count = 0;
    int *results = findSubstring(argv[1], argv + 2, argc - 2, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");
    return 0;
}
