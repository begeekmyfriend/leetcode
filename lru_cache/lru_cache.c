/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

struct entry {
        int key;
        int value;
        struct entry *next;
        struct entry *prev;
};

struct lru_cache {
        int capacity;
        int count;
        struct entry *head;
        struct entry *tail;
};

static struct lru_cache cache;

static void entry_insert(struct entry *p)
{
        p->next = cache.head;
        cache.head->prev = p;
        p->prev = cache.tail;
        cache.tail->next = p;
        cache.head = p;
}

static void entry_remove(struct entry *p)
{
        p->prev->next = p->next;
        p->next->prev = p->prev;
}

static struct entry *entry_search(int key)
{
        int i;
        struct entry *p = cache.head;
        for (i = 0; i < cache.count; i++) {
                if (key == p->key) {
                        return p;
                }
                p = p->next;
        }
        return NULL;
}

static void entry_adjust(struct entry *p)
{
        if (p != cache.head) {
                if (p == cache.tail) {
                        cache.tail = p->prev;
                }
                entry_remove(p);
                entry_insert(p);
        }
}

void lru_cache_init(int capacity)
{
        cache.count = 0;
        cache.capacity = capacity;
        cache.head = cache.tail = NULL; 
}

void lru_cache_free(void)
{
        int i;
        struct entry *e = cache.head;
        struct entry **pp = &cache.head;
        for (i = 0; i < cache.count; i++) {
                *pp = e->next;
                free(e);
                e = *pp;
        }
        cache.count = cache.capacity = 0;
        cache.tail = cache.head = NULL;
}

int lru_cache_get(int key)
{
        struct entry *p = entry_search(key);
        if (p == NULL) {
                return -1;
        }

        entry_adjust(p);
        return cache.head->value;
}

void lru_cache_set(int key, int value)
{
        struct entry *p = entry_search(key);
        if (p == NULL) {
                if (cache.count == cache.capacity) {
                        p = cache.tail;
                } else {
                        p = malloc(sizeof(*p));
                        if (cache.head == NULL) {
                                cache.head = p;
                                cache.tail = p;
                        }
                        p->next = p->prev = p;
                        cache.count++;
                }
        }
        p->key = key;
        p->value = value;
        entry_adjust(p);
}

void lru_cache_dump(void)
{
        struct entry *p = cache.head;
        while (p != cache.tail) {
                printf("%p[%d %d]\n", p, p->key, p->value);
                p = p->next;
        }
        printf("%p[%d %d]\n", p, p->key, p->value);
}

int main(void)
{
#if 1
        lru_cache_init(2);
        printf("key=2, value:%d\n", lru_cache_get(2));
        lru_cache_set(2, 6);
        printf("key=1, value:%d\n", lru_cache_get(1));
        lru_cache_set(1, 5);
        lru_cache_set(1, 2);
        lru_cache_dump();
        printf("key=1, value:%d\n", lru_cache_get(1));
        printf("key=2, value:%d\n", lru_cache_get(2));
#else
        lru_cache_init(1);
        printf("key=0, value:%d\n", lru_cache_get(0));
#endif
        lru_cache_free();
        return 0;
}
