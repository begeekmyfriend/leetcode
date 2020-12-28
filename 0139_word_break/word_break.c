#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define	list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

struct list_head {
    struct list_head *next, *prev;
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

struct word_node {
    char *word;
    struct list_head link;
};

struct dfs_cache {
    int num;
    int cap;
    struct list_head **heads;
};

static struct dfs_cache *resize(struct dfs_cache **caches, int index)
{
    int i;
    struct dfs_cache *cache = caches[index];
    if (cache->num + 1 > cache->cap) {
        cache->cap *= 2;
        struct list_head **heads = malloc(cache->cap * sizeof(*heads));
        for (i = 0; i < cache->cap; i++) {
            if (i < cache->num) {
                 heads[i] = cache->heads[i];
            } else {
                 heads[i] = malloc(sizeof(struct list_head));
                 INIT_LIST_HEAD(heads[i]);
            }
        }
        free(cache->heads);
        cache->heads = heads;
    }

    return cache;
}

static struct dfs_cache *dfs(char *s, char **words, int *sizes, int num,
                             struct dfs_cache **caches, int index)
{
    int i, j;
    struct word_node *wn;
    struct dfs_cache *result;

    if (*s == '\0') {
        return NULL;
    } else if (caches[index] != NULL) {
        return caches[index];
    } else {
        result = malloc(sizeof(*result));
        result->num = 0;
        result->cap = 1;
        result->heads = malloc(sizeof(struct list_head *));
        result->heads[0] = malloc(sizeof(struct list_head));
        INIT_LIST_HEAD(result->heads[0]);
        caches[index] = result;
        for (i = 0; i < num; i++) {
            if (!memcmp(s, words[i], sizes[i])) {
                struct dfs_cache *next = dfs(s + sizes[i], words, sizes, num, caches, index + sizes[i]);
                if (next != NULL) {
                    int k = result->num;
                    for (j = k; j < k + next->num; j++) {
                        result = resize(caches, index);
                        wn = malloc(sizeof(*wn));
                        wn->word = words[i];
                        list_add(&wn->link, result->heads[j]);

                        struct list_head *p;
                        list_for_each(p, next->heads[j - k]) {
                            struct word_node *wnn = list_entry(p, struct word_node, link);
                            wn = malloc(sizeof(*wn));
                            wn->word = wnn->word;
                            list_add_tail(&wn->link, result->heads[j]);
                        }
                        result->num++;
                    }
                } else {
                    return NULL;
                }
            }
        }

        return result;
    }
}

static bool wordBreak(char* s, char** wordDict, int wordDictSize)
{
    if (wordDictSize == 0) {
        return false;
    }

    int i, total = 0;
    int len = strlen(s);
    int *sizes = malloc(wordDictSize * sizeof(int));

    for (i = 0; i < wordDictSize; i++) {
        sizes[i] = strlen(wordDict[i]);
        total += sizes[i];
    }

    struct dfs_cache **caches = malloc(len * sizeof(*caches));
    memset(caches, 0, len * sizeof(*caches));
    return dfs(s, wordDict, sizes, wordDictSize, caches, 0) == NULL;
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
