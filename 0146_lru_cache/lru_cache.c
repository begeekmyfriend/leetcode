#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member), \
         n = list_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

struct list_head {
    struct list_head *next, *prev;
};

typedef struct {
    int capacity;
    int count;
    struct list_head dhead;
    struct list_head hheads[];
} LRUCache;

typedef struct {
    int key;
    int value;
    struct list_head hlink;
    struct list_head dlink;
} LRUNode;

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

static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list);
    list_add(list, head);
}

static inline void list_move_tail(struct list_head *entry, struct list_head *head)
{
    __list_del(entry);
    list_add_tail(entry, head);
}

LRUCache *lRUCacheCreate(int capacity)
{
    int i;
    LRUCache *obj = malloc(sizeof(*obj) + capacity * sizeof(struct list_head));
    obj->count = 0;
    obj->capacity = capacity;
    INIT_LIST_HEAD(&obj->dhead);
    for (i = 0; i < capacity; i++) {
        INIT_LIST_HEAD(&obj->hheads[i]);
    }
    return obj;
}

void lRUCacheFree(LRUCache *obj)
{
    LRUNode *lru, *n;
    list_for_each_entry_safe(lru, n, &obj->dhead, dlink) {
        list_del(&lru->dlink);
        free(lru);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry(lru, &obj->hheads[hash], hlink) {
        if (lru->key == key) {
            /* Move it to header */
            list_move(&lru->dlink, &obj->dhead);
            return lru->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry(lru, &obj->hheads[hash], hlink) {
        if (lru->key == key) {
            list_move(&lru->dlink, &obj->dhead);
            lru->value = value;
            return;
        }
    }

    if (obj->count == obj->capacity) {
        lru = list_last_entry(&obj->dhead, LRUNode, dlink);
        list_del(&lru->dlink);
        list_del(&lru->hlink);
    } else {
        lru = malloc(sizeof(LRUNode));
        obj->count++;
    }
    lru->key = key;
    list_add(&lru->dlink, &obj->dhead);
    list_add(&lru->hlink, &obj->hheads[hash]);
    lru->value = value;
}

void lRUCacheDump(LRUCache *obj)
{
    if (obj == NULL) return;

    int i;
    LRUNode *lru;
    printf(">>> Total %d nodes: \n", obj->count);
    for (i = 0; i < obj->count; i++) {
        printf("hash:%d:", i);
        list_for_each_entry(lru, &obj->hheads[i], hlink) {
            lru = list_entry(lru, LRUNode, hlink);
            if (lru != NULL) {
                printf(" (%d %d)", lru->key, lru->value);
            }
        }
        printf("\n");
    }

    printf(">>> Double list dump\n");
    list_for_each_entry(lru, &obj->dhead, dlink) {
        printf("(%d %d)\n", lru->key, lru->value);
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
