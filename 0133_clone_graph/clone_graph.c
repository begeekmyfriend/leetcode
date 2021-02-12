#include <stdio.h>
#include <stdlib.h>


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

struct UndirectedGraphNode {
    int label;
    struct UndirectedGraphNode *neighbors[100];
    int neighborsCount;
};

struct label_node {
    struct list_head link;
    struct UndirectedGraphNode *gn;
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

static struct UndirectedGraphNode *find(int label, int size, struct list_head *heads)
{
    struct label_node *ln;
    int hash = (label < 0 ? -label : label) % size;
    list_for_each_entry(ln, &heads[hash], link) {
        if (ln->gn->label == label) {
            return ln->gn;
        }
    }
    return NULL;
}

static struct UndirectedGraphNode *dfs(struct UndirectedGraphNode *graph, struct list_head *heads, int size)
{
    if (graph == NULL) {
        return NULL;
    }

    struct UndirectedGraphNode *node = find(graph->label, size, heads);
    if (node != NULL) {
        return node;
    }

    node = malloc(sizeof(*node));
    node->label = graph->label;
    node->neighborsCount = graph->neighborsCount;
    struct label_node *ln = malloc(sizeof(*ln));
    ln->gn = node;
    int hash = (node->label < 0 ? -node->label : node->label) % size;
    list_add(&ln->link, &heads[hash]);

    int i;
    for (i = 0; i < node->neighborsCount; i++) {
        node->neighbors[i] = dfs(graph->neighbors[i], heads, size);
    }

    return node;
}

struct UndirectedGraphNode *cloneGraph(struct UndirectedGraphNode *graph)
{
    int i, cap = 1000;
    struct list_head *heads = malloc(cap * sizeof(*heads));
    for (i = 0; i < cap; i++) {
        INIT_LIST_HEAD(&heads[i]);
    }
    return dfs(graph, heads, cap);
}

int main(void)
{
    struct UndirectedGraphNode n0, n1, n2;
    n0.label = 0;
    n1.label = 1;
    n2.label = 2;
    n0.neighborsCount = 2;
    n1.neighborsCount = 1;
    n2.neighborsCount = 1;
    n0.neighbors[0] = &n1;
    n0.neighbors[1] = &n2;
    n1.neighbors[0] = &n2;
    n2.neighbors[0] = &n2;

    struct UndirectedGraphNode *res = cloneGraph(&n0);
    return 0;
}
