#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, typeof(*pos), member))

struct list_head {
    struct list_head *next, *prev;
};

struct word_node {
    char *word;
    struct list_head node;
    struct list_head sibling;
    struct list_head link;
    int par_num;
    int step;
    struct word_node *parents[];
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

static int BKDRHash(char* str, int size)
{
    int seed = 131; // 31 131 1313 13131 131313 etc.. 
    unsigned int hash = 0 ;
    while (*str != '\0') {
        hash = hash * seed + (*str++);
    }
    return hash % size;
}

static struct word_node *find(char *word, struct list_head *dict, int size, int step)
{
    struct word_node *node;
    int hash = BKDRHash(word, size);
    list_for_each_entry(node, &dict[hash], node) {
        if (!strcmp(node->word, word)) {
            if (node->step == 0 || node->step == step) {
                return node;
            }
        }
    }
    return NULL;
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 **/
char*** findLadders(char* beginWord, char* endWord, char** wordList, int wordListSize, int* returnSize, int** returnColumnSizes)
{
    int i, word_len = strlen(beginWord);
    int hashsize = wordListSize * 2;
    char *word = malloc(word_len + 1);

    struct list_head *dict = malloc(hashsize * sizeof(*dict));
    for (i = 0; i < hashsize; i++) {
        INIT_LIST_HEAD(dict + i);
    }

    struct list_head *level_caches = malloc(wordListSize * sizeof(*level_caches));
    for (i = 0; i < wordListSize; i++) {
        INIT_LIST_HEAD(&level_caches[i]);
    }

    /* Word dictionary */
    *returnSize = 0;
    bool found = false;
    struct word_node *node, *wn;
    for (i = 0; i < wordListSize; i++) {
        node = malloc(sizeof(*node));
        node->word = wordList[i];
        node->step = 0;
        int hash = BKDRHash(wordList[i], hashsize);
        list_add(&node->node, &dict[hash]);
        if (!strcmp(endWord, wordList[i])) {
            found = true;
        }
    }
    if (!found) {
        return NULL;
    }

    /* FIFO */
    struct list_head queue;
    INIT_LIST_HEAD(&queue);

    /* Build tree structure for BFS */
    struct word_node *root = malloc(sizeof(*root) + sizeof(void *));
    root->word = beginWord;
    root->step = 1;
    root->par_num = 1;
    root->parents[0] = NULL;
    list_add_tail(&root->sibling, &level_caches[0]);
    node = find(beginWord, dict, hashsize, 1);
    if (node != NULL) {
        node->step = 1;
    }

    /* BFS with FIFO queue for shortest path */
    struct word_node *first = root;
    while (strcmp(first->word, endWord)) {
        strcpy(word, first->word);
        for (i = 0; i < word_len; i++) {
            char c;
            char o = word[i];
            for (c = 'a'; c <= 'z'; c++) {
                if (c == o) continue;
                word[i] = c;
                node = find(word, dict, hashsize, first->step + 1);
                if (node != NULL) {
                    int enqueue = 1;
                    /* Search in level cache in case of duplication */
                    list_for_each_entry(wn, &level_caches[first->step], sibling) {
                        /* Here we could just check if they are the same reference */
                        if (wn->word == node->word) {
                            enqueue = 0;
                            /* record the parant relation */
                            wn->parents[wn->par_num++] = first;
                            break;
                        }
                    }

                    if (enqueue) {
                        /* new level cache and enqueue */
                        node->step = first->step + 1;
                        struct word_node *new = malloc(sizeof(*new) + 15 * sizeof(void *));
                        new->word = node->word;
                        new->step = node->step;
                        new->par_num = 0;
                        list_add_tail(&new->sibling, &level_caches[first->step]);
                        list_add_tail(&new->link, &queue);
                        new->parents[new->par_num++] = first;
                    }
                }
            }
            word[i] = o;
        }

        if (list_empty(&queue)) {
            return NULL;
        } else {
            /* dequeue */
            first = list_first_entry(&queue, struct word_node, link);
            list_del(&first->link);
        }
    }

    int size = first->step;
    char ***results = malloc(1000 * sizeof(char **));
    int *indexes = malloc(size * sizeof(int));
    memset(indexes, 0, size * sizeof(int));
    struct word_node **nodes = malloc(size * sizeof(*nodes));
    struct word_node *end;
    list_for_each_entry(end, &level_caches[size - 1], sibling) {
        if (!strcmp(end->word, endWord)) {
            int move_on = 1;
            while (move_on) {
                move_on = 0;
                wn = end;
                char **list = results[*returnSize] = malloc(size * sizeof(char *));
                for (i = size - 1; i >= 0; i--) {
                    list[i] = malloc(word_len + 1);
                    strcpy(list[i], wn->word);
                    nodes[i] = wn;
                    wn = wn->parents[indexes[i]];
                }

                /* Switch to another branch */
                for (i = 0; i < size; i++) {
                    if (indexes[i] < nodes[i]->par_num - 1) {
                        indexes[i]++;
                        /* common prefix  */
                        memset(indexes, 0, i * sizeof(int));
                        move_on = 1;
                        break;
                    }
                }

                (*returnSize)++;
            }
        }
    }

    *returnColumnSizes = malloc(*returnSize * sizeof(int));
    for (i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = size;
    }
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test begin end dict...\n");
        exit(-1);
    }

    int i, j, *sizes, count = 0;
    char ***lists = findLadders(argv[1], argv[2], argv + 3, argc - 3, &count, &sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}
