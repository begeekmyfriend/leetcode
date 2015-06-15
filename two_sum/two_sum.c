/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct hlist_node;

struct hlist_head
{
        struct hlist_node *first;
};

struct hlist_node
{
        struct hlist_node *next, **pprev;
};

static inline void
INIT_HLIST_HEAD(struct hlist_head *h)
{
        h->first = NULL;
}

static inline void
INIT_HLIST_NODE(struct hlist_node *n)
{
        n->next = NULL;
        n->pprev = NULL;
}

static inline int
hlist_unhashed(struct hlist_node *n)
{
        return !n->pprev;
}

static inline int
hlist_empty(struct hlist_head *h)
{
        return !h->first;
}

static inline void
hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
        if (h->first != NULL) {
                h->first->pprev = &n->next;
        }
        n->next = h->first;
        n->pprev = &h->first;
        h->first = n;
}

static inline void
__hlist_del(struct hlist_node *n)
{
        struct hlist_node *next = n->next;
        struct hlist_node **pprev = n->pprev;
        *pprev = next;
        if (next != NULL) {
                next->pprev = pprev;
        }
}

static inline void
hlist_del(struct hlist_node *n)
{
        __hlist_del(n);
}

static inline void
hlist_add_before(struct hlist_node *n, struct hlist_node *next)
{
        n->next = next;
        n->pprev = next->pprev;
        *(n->pprev) = n;
        next->pprev = &n->next;
}

static inline void
hlist_add_behind(struct hlist_node *n, struct hlist_node *prev)
{
        struct hlist_node *next = prev->next;
        n->next = next;
        prev->next = n;
        n->pprev = &prev->next;
        if (next != NULL) {
                next->pprev = &n->next;
        }
}

#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define hlist_entry(ptr, type, member) \
        container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
        for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
        for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

int *
twosum(int numbers[], int n, int target)
{
        int i, j;
        struct hash_table
        {
                struct hlist_head h;
        };
        struct plus_elem
        {
                int index;
                int num;
                struct hlist_node n;
        };

        struct hash_table *ht = malloc(n * sizeof(*ht));
        if (ht == NULL) {
                return NULL;
        }
        for (i = 0; i < n; i++) {
                INIT_HLIST_HEAD(&ht[i].h);
        }
        struct plus_elem *elems = malloc(n * sizeof(*elems));
        if (elems == NULL) {
                return NULL;
        }
        for (i = 0; i < n; i++) {
                elems[i].num = 0;
                INIT_HLIST_NODE(&elems[i].n);
        }

        for (i = 0; i < n; i++) {
                int num = numbers[i] < 0 ? -numbers[i] : numbers[i];
                int hash = num % n;
                elems[i].index = i + 1;
                elems[i].num = numbers[i];
                hlist_add_head(&elems[i].n, &ht[hash].h);
        }

        for (i = 0; i < n; i++) {
                int num = target - numbers[i];
                int h1 = numbers[i] < 0 ? -numbers[i] % n : numbers[i] % n;
                int h2 = num < 0 ? -num % n : num % n;
                int i1 = 0, i2 = 0;
                struct hlist_node *pos;
                hlist_for_each(pos, &ht[h1].h) {
                        struct plus_elem *elem = hlist_entry(pos, struct plus_elem, n);
                        if (elem->num == numbers[i]) {
                                i1 = elem->index;
                                break;
                        }
                }
                hlist_for_each(pos, &ht[h2].h) {
                        struct plus_elem *elem = hlist_entry(pos, struct plus_elem, n);
                        if (elem->num == num) {
                                if (i1 != elem->index) {
                                        i2 = elem->index;
                                        break;
                                }
                        }
                }
                if (i1 > 0 && i2 > 0) {
                        int *indexes = malloc(2 * sizeof(int));
                        if (indexes == NULL) {
                                break;
                        }
                        indexes[0] = i1 < i2 ? i1 : i2;
                        indexes[1] = i1 > i2 ? i1 : i2;
                        return indexes;
                }
        }

        return NULL;
}

int
main(void)
{
        //int numbers[] = {-1, -2, -3, -4, -5};
        //int target = -8;
        int numbers[] = {0,4,3,0};
        int target = 0;
        int *indexes = twosum(numbers, sizeof(numbers) / sizeof(numbers[0]), target);
        if (indexes != NULL) {
                printf("%d %d\n", indexes[0], indexes[1]);
        } else {
                printf("Not found\n");
        }

        return 0;
}
