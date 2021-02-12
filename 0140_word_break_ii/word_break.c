#include <stdio.h>
#include <stdlib.h>
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
    struct list_head link;
};

struct solution {
    int count;
    struct list_head heads[];
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

static void new_word_add(struct list_head *head, char *word)
{
    struct word_node *wn = malloc(sizeof(*wn));
    wn->word = word;
    list_add_tail(&wn->link, head);
}

static struct solution *dfs(char *s, char **words, int *lens, int size,
                            struct solution **sols, int index)
{
    int i, j;
    if (*s == '\0') {
        return NULL;
    } else if (sols[index] != NULL) {
        return sols[index];
    } else {
        struct solution *sol = malloc(sizeof(*sol) + 60 * sizeof(struct list_head));
        sol->count = 0;
        sols[index] = sol;
        for (i = 0; i < size; i++) {
            if (!strncmp(s, words[i], lens[i])) {
                /* post-order traverse */
                struct solution *sub_sol = dfs(s + lens[i], words, lens, size, sols, index + lens[i]);
                if (sub_sol != NULL) {
                    int k = sol->count;
                    for (j = k; j < k + sub_sol->count; j++) {
                        /* Append all sub-solutions */
                        INIT_LIST_HEAD(&sol->heads[j]);
                        new_word_add(&sol->heads[j], words[i]);
                        struct word_node *wn;
                        list_for_each_entry(wn, &sub_sol->heads[j - k], link) {
                            new_word_add(&sol->heads[j], wn->word);
                        }
                        sol->count++;
                    }
                } else {
                    /* leaf node */
                    INIT_LIST_HEAD(&sol->heads[0]);
                    new_word_add(&sol->heads[sol->count++], words[i]);
                }
            }
        }
        return sol;
    }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **wordBreak(char* s, char** wordDict, int wordDictSize, int *returnSize)
{
    if (wordDictSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int i, total = 0;
    int len = strlen(s);
    int *lens = malloc(wordDictSize * sizeof(int));

    /* Add into hash list */
    for (i = 0; i < wordDictSize; i++) {
        lens[i] = strlen(wordDict[i]);
        total += lens[i];
    }

    struct solution **sols = malloc(len * sizeof(void *));
    memset(sols, 0, len * sizeof(void *));
    struct solution *sol = dfs(s, wordDict, lens, wordDictSize, sols, 0);

    char **results = malloc(sol->count * sizeof(char *));
    for (i = 0; i < sol->count; i++) {
        results[i] = malloc(total + 100);
        char *p = results[i];
        struct word_node *wn;
        list_for_each_entry(wn, &sol->heads[i], link) {
            char *q = wn->word;
            while ((*p++ = *q++) != '\0') {}
            *(p - 1) = ' ';
        }
        *(p - 1) = '\0';
    }

    *returnSize = sol->count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test word dictionary...\n");
        exit(-1);
    }

    int i, count = 0;
    char **list = wordBreak(argv[1], argv + 2, argc - 2, &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }
    return 0;
}
