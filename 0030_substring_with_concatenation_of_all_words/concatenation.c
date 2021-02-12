#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, typeof(*pos), member))

struct list_head {
    struct list_head *next, *prev;
};

struct word_node {
    char *word;
    int index;
    struct list_head link;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static inline void list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

static inline void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

static inline int BKDRHash(char *s, size_t size)
{
    int seed = 131; /* 131 1313 13131... */
    unsigned long hash = 0;
    while (*s != '\0') {
        hash = hash * seed + *s++;
    }
    return hash % size;
}

static int find(char *word, struct list_head *heads, int size)
{
    struct word_node *wn;
    int hash = BKDRHash(word, size);
    list_for_each_entry(wn, &heads[hash], link) {
        if (!strcmp(wn->word, word)) {
            return wn->index;
        }
    }
    return -1;
}

static void add(char **words, int index, struct list_head *heads, int size, int *freqs)
{
    struct word_node *wn;
    int hash = BKDRHash(words[index], size);
    list_for_each_entry(wn, &heads[hash], link) {
        if (!strcmp(wn->word, words[index])) {
            freqs[wn->index]++;
            return;
        }
    }
    wn = malloc(sizeof(*wn));
    wn->word = words[index];
    wn->index = index;
    list_add(&wn->link, &heads[hash]);
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
    struct list_head *heads = malloc(hash_size * sizeof(*heads));
    for (i = 0; i < hash_size; i++) {
        INIT_LIST_HEAD(&heads[i]);
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
    for (i = 0; s[i + len - 1] != '\0'; i++) {
        memcpy(word, s + i, len);
        indexes[i] = find(word, heads, hash_size);
    }

    int *results = malloc(cap * sizeof(int));
    int *fqs = malloc(wordsSize * sizeof(int));
    for (i = 0; s[i + length] != '\0'; i++) {
        memset(fqs, 0, wordsSize * sizeof(int));
        for (j = 0; j < wordsSize; j++) {
            /* concatenation */
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
