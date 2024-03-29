#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, __typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, __typeof(*pos), member))

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
    int step;
    char *word;
    struct list_head node;
    struct list_head link;
};

static int BKDRHash(char* str, int size)
{
    int seed = 131; // 31 131 1313 13131 131313 etc.. 
    unsigned int hash = 0 ;
    while (*str != '\0') {
        hash = hash * seed + (*str++);
    }
    return hash % size;
}

static struct word_node *find(char *word, struct list_head *dict, int size)
{
    struct word_node *node;
    int hash = BKDRHash(word, size);
    list_for_each_entry(node, &dict[hash], node) {
        if (node->step == 0 && !strcmp(node->word, word)) {
            return node;
        }
    }
    return NULL;
}

static int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize)
{
    int i, len = strlen(beginWord);
    char *word = malloc(len + 1);
    struct list_head queue;
    struct word_node *node;

    struct list_head *dict = malloc(wordListSize * sizeof(*dict));
    for (i = 0; i < wordListSize; i++) {
        INIT_LIST_HEAD(dict + i);
    }

    /* Add into hash list */
    bool found = false;
    for (i = 0; i < wordListSize; i++) {
        node = malloc(sizeof(*node));
        node->word = wordList[i];
        node->step = 0;
        int hash = BKDRHash(wordList[i], wordListSize);
        list_add(&node->node, &dict[hash]);
        if (!strcmp(endWord, wordList[i])) {
            found = true;
        }
    }
    if (!found) {
        return 0;
    }

    /* FIFO */
    INIT_LIST_HEAD(&queue);
    struct word_node *first = malloc(sizeof(*node));
    first->word = beginWord;
    first->step = 1;

    /* BFS with FIFO for shortest path */
    while (strcmp(first->word, endWord)) {
        strcpy(word, first->word);
        for (i = 0; i < len; i++) {
            char c;
            char o = word[i];
            for (c = 'a'; c <= 'z'; c++) {
                if (c == o) continue;
                word[i] = c;
                node = find(word, dict, wordListSize);
                if (node != NULL) {
                    /* enqueue */
                    list_add_tail(&node->link, &queue);
                    node->step = first->step + 1;
                }
            }
            word[i] = o;
        }

        if (list_empty(&queue)) {
            return 0;
        } else {
            /* dequeue */
            first = list_first_entry(&queue, struct word_node, link);
            list_del(&first->link);
        }
    }

    return first->step;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test begin end dict...\n");
        exit(-1);
    }

    printf("%d\n", ladderLength(argv[1], argv[2], argv + 3, argc - 3));
    return 0;
}
