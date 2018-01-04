#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

#define	list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define	list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

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

static inline void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next != NULL) {
        next->pprev = pprev;
    }
}

struct list_head {
    struct list_head *next, *prev;
};

static inline void
INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int
list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline void
__list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void
list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static inline void
list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

static inline void
__list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static inline void
list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

static inline void
list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list);
    list_add(list, head);
}

static inline void
list_move_tail(struct list_head *entry, struct list_head *head)
{
    __list_del(entry);
    list_add_tail(entry, head);
}

typedef struct {
    int capacity;
    int count;
    struct list_head dhead;
    struct hlist_head hhead[];
} LRUCache;

typedef struct {
    int key;
    int value;
    struct hlist_node node;
    struct list_head link;
} LRUNode;


LRUCache *lRUCacheCreate(int capacity)
{
    int i;
    LRUCache *obj = malloc(2 * sizeof(int) + sizeof(struct list_head) + capacity * sizeof(struct hlist_head));
    obj->count = 0;
    obj->capacity = capacity;
    INIT_LIST_HEAD(&obj->dhead);
    for (i = 0; i < capacity; i++) {
        INIT_HLIST_HEAD(&obj->hhead[i]);
    }
    return obj;
}

void lRUCacheFree(LRUCache *obj)
{
    struct list_head *pos, *n;
    list_for_each_safe(pos, n, &obj->dhead) {
        LRUNode *cache = list_entry(pos, LRUNode, link);
        list_del(&cache->link);
        free(cache);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key)
{
    int hash = key % obj->capacity;
    struct hlist_node *pos;
    hlist_for_each(pos, &obj->hhead[hash]) {
        LRUNode *cache = list_entry(pos, LRUNode, node);
        if (cache->key == key) {
            /* Move it to header */
            list_move(&cache->link, &obj->dhead);
            return cache->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode *cache = NULL;
    int hash = key % obj->capacity;
    struct hlist_node *pos;
    hlist_for_each(pos, &obj->hhead[hash]) {
        LRUNode *c = list_entry(pos, LRUNode, node);
        if (c->key == key) {
            list_move(&c->link, &obj->dhead);
            cache = c;
        }
    }

    if (cache == NULL) {
        if (obj->count == obj->capacity) {
            cache = list_last_entry(&obj->dhead, LRUNode, link);
            list_move(&cache->link, &obj->dhead);
            hlist_del(&cache->node);
            hlist_add_head(&cache->node, &obj->hhead[hash]);
        } else {
            cache = malloc(sizeof(LRUNode));
            hlist_add_head(&cache->node, &obj->hhead[hash]);
            list_add(&cache->link, &obj->dhead);
            obj->count++;
        }
        cache->key = key;
    }
    cache->value = value;
}

void lRUCacheDump(LRUCache *obj)
{
    if (obj == NULL) return;

    int i;
    LRUNode *cache;
    printf(">>> Total %d nodes: \n", obj->count);
    for (i = 0; i < obj->count; i++) {
        printf("hash:%d:", i);
        struct hlist_node *pos;
        hlist_for_each(pos, &obj->hhead[i]) {
            cache = list_entry(pos, LRUNode, node);
            if (cache != NULL) {
                printf(" (%d %d)", cache->key, cache->value);
            }
        }
        printf("\n");
    }

    printf(">>> Double list dump\n");
    struct list_head *p;
    list_for_each(p, &obj->dhead) {
        cache = list_entry(p, LRUNode, link);
        printf("(%d %d)\n", cache->key, cache->value);
    }
}

int main(void)
{
    LRUCache *obj;
    obj = lRUCacheCreate(2);
    printf("put 1, 1\n");
    lRUCachePut(obj, 1, 1);
    printf("put 2, 2\n");
    lRUCachePut(obj, 2, 2);
    printf("get 1, %d\n", lRUCacheGet(obj, 1));
    printf("put 3, 3\n");
    lRUCachePut(obj, 3, 3);
    printf("get 2, %d\n", lRUCacheGet(obj, 2));
    printf("put 4, 4\n");
    lRUCachePut(obj, 4, 4);
    printf("get 1, %d\n", lRUCacheGet(obj, 1));
    printf("get 3, %d\n", lRUCacheGet(obj, 3));
    printf("get 4, %d\n", lRUCacheGet(obj, 4));
//#if 1
//    obj = lRUCacheCreate(2);
//    lRUCacheDump(obj);
//    printf("get 2, %d\n", lRUCacheGet(obj, 2));
//    printf("put 2, 6\n");
//    lRUCachePut(obj, 2, 6);
//    lRUCacheDump(obj);
//    printf("get 1, %d\n", lRUCacheGet(obj, 1));
//    printf("put 1, 5\n");
//    lRUCachePut(obj, 1, 5);
//    lRUCacheDump(obj);
//    printf("put 1, 2\n");
//    lRUCachePut(obj, 1, 2);
//    lRUCacheDump(obj);
//    printf("get 1, %d\n", lRUCacheGet(obj, 1));
//    printf("get 2, %d\n", lRUCacheGet(obj, 2));
//    lRUCacheFree(obj);
//#else
//    obj = lRUCacheCreate(2);
//    printf("put 2, 1\n");
//    lRUCachePut(obj, 2, 1);
//    printf("put 1, 1\n");
//    lRUCachePut(obj, 1, 1);
//    lRUCacheDump(obj);
//    printf("get 2, %d\n", lRUCacheGet(obj, 2));
//    lRUCacheDump(obj);
//    printf("put 4, 1\n");
//    lRUCachePut(obj, 4, 1);
//    lRUCacheDump(obj);
//    printf("get 1, %d\n", lRUCacheGet(obj, 1));
//    printf("get 2, %d\n", lRUCacheGet(obj, 2));
//    lRUCacheFree(obj);
//#endif

    return 0;
}
