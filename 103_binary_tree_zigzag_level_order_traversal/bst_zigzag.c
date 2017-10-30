#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BST_MAX_LEVEL 800

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

#define	list_for_each(p, head) \
	for (p = (head)->next; p != (head); p = p->next)

#define	list_for_each_reverse(p, head) \
	for (p = (head)->prev; p != (head); p = p->prev)

#define	list_for_each_safe(p, n, head) \
	for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

#define	list_for_each_safe_reverse(p, n, head) \
	for (p = (head)->prev, n = p->prev; p != (head); p = n, n = p->prev)

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct list_head {
    struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
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
    struct TreeNode *node;
    struct list_head link;
};

static struct bfs_node *node_new(struct list_head *free_list, struct TreeNode *node)
{
    struct bfs_node *new;
    if (list_empty(free_list)) {
        new = malloc(sizeof(*new));
    } else {
        new = list_first_entry(free_list, struct bfs_node, link);
        list_del(&new->link);
    }
    new->node = node;
    return new;
}

static void queue(struct list_head *parents, struct list_head *children, int reverse,
                  struct list_head *free_list, int **results, int *col_sizes, int level)
{
    struct list_head *p, *n;
    struct bfs_node *new, *parent;

    list_for_each(p, parents) {
        parent = list_entry(p, struct bfs_node, link);
        if (parent->node->left != NULL) {
            new = node_new(free_list, parent->node->left);
            list_add_tail(&new->link, children);
        }
        if (parent->node->right != NULL) {
            new = node_new(free_list, parent->node->right);
            list_add_tail(&new->link, children);
        }
        col_sizes[level]++;
    }

    int i = 0;
    results[level] = malloc(col_sizes[level] * sizeof(int));
    if (reverse) {
        list_for_each_safe_reverse(p, n, parents) {
            parent = list_entry(p, struct bfs_node, link);
            results[level][i++] = parent->node->val;
            list_del(p);
            list_add(p, free_list);
        }
    } else {
        list_for_each_safe(p, n, parents) {
            parent = list_entry(p, struct bfs_node, link);
            results[level][i++] = parent->node->val;
            list_del(p);
            list_add(p, free_list);
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static int** zigzagLevelOrder(struct TreeNode* root, int** columnSizes, int* returnSize)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    struct list_head free_list;
    struct list_head q0;
    struct list_head q1;
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q0);
    INIT_LIST_HEAD(&q1);

    int **results = malloc(BST_MAX_LEVEL * sizeof(int *));
    *columnSizes = malloc(BST_MAX_LEVEL * sizeof(int));
    memset(*columnSizes, 0, BST_MAX_LEVEL * sizeof(int));

    int level = 0;
    struct bfs_node *new = node_new(&free_list, root);
    list_add_tail(&new->link, &q0);

    while (!list_empty(&q0) || !list_empty(&q1)) {
        if (level & 0x1) {
            queue(&q1, &q0, 1, &free_list, results, *columnSizes, level);
        } else {
            queue(&q0, &q1, 0, &free_list, results, *columnSizes, level);
        }
        level++;
    }

    *returnSize = level;
    return results;
}

int main(void)
{
#if 1
    struct TreeNode root;
    root.val = 3;

    struct TreeNode node1[2];
    node1[0].val = 9;
    node1[1].val = 20;

    struct TreeNode node2[4];
    node2[2].val = 15;
    node2[3].val = 7;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = NULL;
    node1[0].right = NULL;
    node1[1].left = &node2[2];
    node1[1].right = &node2[3];
#else
    struct TreeNode root;
    root.val = 1;

    struct TreeNode node1[2];
    node1[0].val = 2;
    node1[1].val = 3;

    struct TreeNode node2[4];
    node2[0].val = 4;
    node2[3].val = 5;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = &node2[0];
    node1[0].right = NULL;
    node1[1].left = NULL;
    node1[1].right = &node2[3];
#endif

    node2[0].left = NULL;
    node2[0].right = NULL;
    node2[1].left = NULL;
    node2[1].right = NULL;
    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    int i, j, count = 0, *col_sizes;
    int **lists = zigzagLevelOrder(&root, &col_sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}
