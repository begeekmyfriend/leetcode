#include <stdio.h>
#include <stdlib.h>


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

struct list_head {
    struct list_head *next, *prev;
};

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct queue_node {
    struct Node *node;
    struct list_head link;
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

static struct queue_node *node_new(struct Node *node, struct list_head *free_list)
{
    struct queue_node *qn;
    if (list_empty(free_list)) {
        qn = malloc(sizeof(*qn));
    } else {
        qn = list_first_entry(free_list, struct queue_node, link);
        list_del(&qn->link);
    }
    qn->node = node;
    return qn;
}

static void node_free(struct queue_node *qn, struct list_head *free_list)
{
    list_del(&qn->link);
    list_add_tail(&qn->link, free_list);
}

struct Node *connect(struct Node *root)
{
    if (root == NULL) {
        return root;
    }

    struct list_head free_list;
    struct list_head q;
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q);

    int i, level_size = 1;
    struct queue_node *new = node_new(root, &free_list);
    list_add_tail(&new->link, &q);

    while (!list_empty(&q)) {
        struct Node *prev = NULL;
        int size = level_size;
        for (i = 0; i < size; i++) {
            struct queue_node *qn = list_first_entry(&q, struct queue_node, link);
            if (prev != NULL) {
                prev->next = qn->node;
            }
            prev = qn->node;

            if (qn->node->left != NULL) {
                new = node_new(qn->node->left, &free_list);
                list_add_tail(&new->link, &q);
                level_size++;
            }
            if (qn->node->right != NULL) {
                new = node_new(qn->node->right, &free_list);
                list_add_tail(&new->link, &q);
                level_size++;
            }

            node_free(qn, &free_list);
        }
    }

    return root;
}

int main(int argc, char **argv)
{
    struct Node root, n1[2], n2[4], n3[8];
#if 0
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
#else
    root.val = 1;
    n1[0].val = 2;
    n1[1].val = 3;
    n2[0].val = 4;
    n2[1].val = 5;
    n2[3].val = 7;

    root.left = &n1[0];
    root.right = &n1[1];
    n1[0].left = &n2[0];
    n1[0].right = &n2[1];
    n1[0].next = NULL;
    n1[1].left = NULL;
    n1[1].right = &n2[3];
    n1[1].next = NULL;
    n2[0].left = NULL;
    n2[0].right = NULL;
    n2[0].next = NULL;
    n2[1].left = NULL;
    n2[1].right = NULL;
    n2[1].next = NULL;
    n2[3].left = NULL;
    n2[3].right = NULL;
    n2[3].next = NULL;
#endif

    connect(&root);
    return 0;
}
