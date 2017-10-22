#include <stdio.h>
#include <stdlib.h>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
};

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

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

struct bfs_node {
    struct TreeLinkNode *node;
    struct list_head link;
};

static struct bfs_node *node_fetch(struct list_head *free_list, struct TreeLinkNode *node)
{
    struct bfs_node *bn = list_first_entry(free_list, struct bfs_node, link);
    list_del(&bn->link);
    bn->node = node;
    return bn;
}

static void queue(struct list_head *parents, struct list_head *children, struct list_head *free_list)
{
    struct list_head *p, *n;
    struct TreeLinkNode *prev = NULL;
    list_for_each_safe(p, n, parents) {
        struct bfs_node *new;
        struct bfs_node *parent = list_entry(p, struct bfs_node, link);
        struct TreeLinkNode *lch = parent->node->left;
        struct TreeLinkNode *rch = parent->node->right;
        if (lch != NULL) {
            if (prev != NULL) {
                prev->next = lch;
            }
            prev = lch;
            new = node_fetch(free_list, lch);
            list_add_tail(&new->link, children);
        }
        if (rch != NULL) {
            if (prev != NULL) {
                prev->next = rch;
            }
            prev = rch;
            new = node_fetch(free_list, rch);
            list_add_tail(&new->link, children);
        }

        /* return */
        list_del(p);
        list_add(p, free_list);
    }
}

static void connect(struct TreeLinkNode *root)
{
    if (root == NULL) {
        return;
    }

    struct list_head free_list;
    struct list_head q0;
    struct list_head q1;
    struct bfs_node nodes[4096];
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q0);
    INIT_LIST_HEAD(&q1);

    int i;
    for (i = 0; i < 4096; i++) {
        list_add(&nodes[i].link, &free_list);
    }

    int level = 0;
    struct bfs_node *new = node_fetch(&free_list, root);
    list_add_tail(&new->link, &q0);

    while (!list_empty(&q0) || !list_empty(&q1)) {
        if (level & 0x1) {
            queue(&q1, &q0, &free_list);
        } else {
            queue(&q0, &q1, &free_list);
        }
        level++;
    }
}

int main(int argc, char **argv)
{
    struct TreeLinkNode root, n1[2], n2[4], n3[8];
    root.val = 5;
    n1[0].val = 4;
    n1[1].val = 8;
    n2[0].val = 11;
    n2[2].val = 13;
    n2[3].val = 4;
    n3[0].val = 7;
    n3[1].val = 2;
    n3[6].val = 5;
    n3[7].val = 1;

    root.left = &n1[0];
    root.right = &n1[1];
    n1[0].left = &n2[0];
    n1[0].right = NULL;
    n1[0].next = NULL;
    n1[1].left = &n2[2];
    n1[1].right = &n2[3];
    n1[1].next = NULL;
    n2[0].left = &n3[0];
    n2[0].right = &n3[1];
    n2[0].next = NULL;
    n2[2].left = NULL;
    n2[2].right = NULL;
    n2[2].next = NULL;
    n2[3].left = &n3[6];
    n2[3].right = &n3[7];
    n2[3].next = NULL;
    n3[0].left = NULL;
    n3[0].right = NULL;
    n3[0].next = NULL;
    n3[1].left = NULL;
    n3[1].right = NULL;
    n3[1].next = NULL;
    n3[6].left = NULL;
    n3[6].right = NULL;
    n3[6].next = NULL;
    n3[7].left = NULL;
    n3[7].right = NULL;
    n3[7].next = NULL;

    connect(&root);
    return 0;
}
