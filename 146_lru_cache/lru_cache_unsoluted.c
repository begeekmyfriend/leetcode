#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))
#define	list_entry(ptr, type, field)  container_of(ptr, type, field)
#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)
#define	list_for_each(p, head) for (p = (head)->next; p != (head); p = p->next)
#define	list_for_each_safe(p, n, head) for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)
#define skip_list_foreach(pos, end) for (; pos != end; pos = pos->next)
#define skip_list_foreach_safe(pos, n, end) for (n = pos->next; pos != end; pos = n, n = pos->next)

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list) {
	list->next = list->prev = list;
}

static inline int list_empty(const struct list_head *head) {
	return (head->next == head);
}

static inline int list_is_first(const struct list_head *list, const struct list_head *head) {
	return list->prev == head;
}

static inline int list_is_last(const struct list_head *list, const struct list_head *head) {
	return list->next == head;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next) {
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *_new, struct list_head *head) {
	__list_add(_new, head, head->next);
}

static inline void list_add_tail(struct list_head *_new, struct list_head *head) {
	__list_add(_new, head->prev, head);
}

static inline void __list_del(struct list_head *entry) {
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
}

static inline void list_del(struct list_head *entry) {
	__list_del(entry);
	entry->next = entry->prev = NULL;
}

static inline void list_move(struct list_head *list, struct list_head *head) {
	__list_del(list);
	list_add(list, head);
}

static inline void list_move_tail(struct list_head *entry, struct list_head *head) {
	__list_del(entry);
	list_add_tail(entry, head);
}

struct skip_node {
    int key;
    int value;
    struct list_head d_link;
    struct list_head sk_link[0];
};

#define MAX_LEVEL 12
struct skip_list {
    int level;
    struct list_head head[MAX_LEVEL];
};

struct lru_cache {
    void *buffer;
    struct skip_list sk_list;
    struct list_head d_list;
    int capacity;
    int count;
};

static struct lru_cache cache;

static int random_level(void) {
    const double p = 0.25;
    int level = 1;
    while ((random() & 0xffff) < 0xffff * p) {
        level++;
    }
    return level > MAX_LEVEL ? MAX_LEVEL : level;
}

static struct skip_node *skip_node_new(int level, int key) {
    struct skip_node *node = malloc(sizeof(*node) + level * sizeof(struct list_head));
    if (node != NULL) {
        int i;
        for (i = 0; i < level; i++) {
            INIT_LIST_HEAD(&node->sk_link[i]);
        }
        node->key = key;
    }
    return node;
}

static void skip_node_delete(struct skip_node *node) {
    free(node);
}

static struct skip_node *skip_list_search(struct skip_list *sk_list, int key) {
    int i = sk_list->level - 1;
    struct list_head *pos = &sk_list->head[i];
    struct list_head *end = &sk_list->head[i];
    for (; i >= 0; i--) {
        struct skip_node *node;
        pos = pos->next;
        skip_list_foreach(pos, end) {
            node = list_entry(pos, struct skip_node, sk_link[i]);
            if (node->key == key) {
                return node;
            } else if (node->key > key) {
                end = &node->sk_link[i];
                break;
            }
        }
        pos = end->prev;
        pos--;
        end--;
    }
    return NULL;
}

static struct skip_node *skip_list_insert(struct skip_list *sk_list, int key) {
    int level = random_level();
    if (level > sk_list->level) {
        sk_list->level = level;
    }

    struct skip_node *node = skip_node_new(level, key);
    if (node != NULL) {
        int i = sk_list->level - 1;
        struct list_head *pos = &sk_list->head[i];
        struct list_head *end = &sk_list->head[i];

        for (; i >= 0; i--) {
            struct skip_node *n;
            pos = pos->next;
            skip_list_foreach(pos, end) {
                n = list_entry(pos, struct skip_node, sk_link[i]);
                if (n->key >= key) {
                    end = &n->sk_link[i];
                    break;
                }
            }
            pos = end->prev;
            if (i < level) {
                __list_add(&node->sk_link[i], pos, end);
            }
            pos--;
            end--;
        }
    }
    return node;
}

static void __delete(struct skip_list *sk_list, struct skip_node *node, int level) {
    int i;
    for (i = 0; i < level; i++) {
        list_del(&node->sk_link[i]);
        if (list_empty(&sk_list->head[i])) {
            sk_list->level--;
        }
    }
    skip_node_delete(node);
}

static void skip_list_delete(struct skip_list *sk_list, int key) {
    int i = sk_list->level - 1;
    struct list_head *pos = &sk_list->head[i];
    struct list_head *end = &sk_list->head[i];
    for (; i >= 0; i--) {
        struct list_head *n;
        pos = pos->next;
        skip_list_foreach_safe(pos, n, end) {
            struct skip_node *node = list_entry(pos, struct skip_node, sk_link[i]);
            if (node->key == key) {
                __delete(sk_list, node, i + 1);
            }
        }
        pos = end->prev;
        pos--;
        end--;
    }
}

void lruCacheInit(int capacity) {
    int i;
    cache.count = 0;
    cache.capacity = capacity;
    INIT_LIST_HEAD(&cache.d_list);
    cache.sk_list.level = 1;
    for (i = 0; i < MAX_LEVEL; i++) {
        INIT_LIST_HEAD(&cache.sk_list.head[i]);
    }
}

void lruCacheFree(void) {
    struct list_head *pos, *n;
    list_for_each_safe(pos, n, &cache.sk_list.head[0]) {
        struct skip_node *node = list_entry(pos, struct skip_node, sk_link[0]);
        skip_node_delete(node);
    }
    lruCacheInit(0);
}

int lruCacheGet(int key) {
    struct skip_node *node = skip_list_search(&cache.sk_list, key);
    if (node != NULL) {
        list_move(&node->d_link, &cache.d_list);
        return node->value;
    } else {
        return -1;
    }
}

void lruCacheSet(int key, int value) {
    struct skip_node *node = skip_list_search(&cache.sk_list, key);
    if (node != NULL) {
        list_move(&node->d_link, &cache.d_list);
    } else {
        if (cache.count == cache.capacity) {
            node = list_last_entry(&cache.d_list, struct skip_node, d_link);
            list_del(&node->d_link);
            skip_list_delete(&cache.sk_list, node->key);
        } else {
            cache.count++;
        }
        node = skip_list_insert(&cache.sk_list, key);
        list_add(&node->d_link, &cache.d_list);
    }
    node->value = value;
}

void lruCacheDump(void) {
        struct list_head *pos;

        printf("\n>>> Total %d nodes: \n", cache.count);
        pos = cache.sk_list.head[0].next;
        skip_list_foreach(pos, &cache.sk_list.head[0]) {
                struct skip_node *node = list_entry(pos, struct skip_node, sk_link[0]);
                printf("%d %d\n", node->key, node->value);
        }

        printf(">>> Double list dump\n");
        list_for_each(pos, &cache.d_list) {
                struct skip_node *node = list_entry(pos, struct skip_node, d_link);
                printf("%d %d\n", node->key, node->value);
        }
}

int main(void)
{
        lruCacheInit(2);
        printf("set 2, 1\n");
        lruCacheSet(2, 1);
        printf("set 1, 1\n");
        lruCacheSet(1, 1);
        printflruCacheSet("get 2, %d\n", lruCacheGet(2));
        printf("set 4, 1\n");
        lruCacheSet(4, 1);
        printf("get 1, %d\n", lruCacheGet(1));
        printf("get 2, %d\n", lruCacheGet(2));
        lruCacheFree();

        return 0;
}
