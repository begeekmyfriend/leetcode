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

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct list_head {
    struct list_head *next, *prev;
};

struct queue_node {
    struct TreeNode *node;
    struct list_head link;
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

static struct queue_node *node_new(struct TreeNode *node, struct list_head *free_list)
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
    list_add(&qn->link, free_list);
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 **/
static int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    struct list_head free_list;
    struct list_head q;
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q);

    int **results = malloc(BST_MAX_LEVEL * sizeof(int *));
    *returnColumnSizes = malloc(BST_MAX_LEVEL * sizeof(int));
    memset(*returnColumnSizes, 0, BST_MAX_LEVEL * sizeof(int));

    /* Add root node */
    struct queue_node *new = node_new(root, &free_list);
    list_add_tail(&new->link, &q);

    int i, level = 0;
    (*returnColumnSizes)[level]++;
    while (!list_empty(&q)) {
        int size = (*returnColumnSizes)[level];
        results[level] = malloc(size * sizeof(int));
        for (i = 0; i < size; i++) {
            struct queue_node *qn = list_first_entry(&q, struct queue_node, link);
            results[level][i] = qn->node->val;

            if (qn->node->left != NULL) {
                new = node_new(qn->node->left, &free_list);
                list_add_tail(&new->link, &q);
                (*returnColumnSizes)[level + 1]++;
            }
            if (qn->node->right != NULL) {
                new = node_new(qn->node->right, &free_list);
                list_add_tail(&new->link, &q);
                (*returnColumnSizes)[level + 1]++;
            }

            node_free(qn, &free_list);
        }
        level++;
    }

    *returnSize = level;
    return results;
}

int main(void)
{
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

    node2[0].left = NULL;
    node2[0].right = NULL;
    node2[1].left = NULL;
    node2[1].right = NULL;
    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    int i, j, count = 0, *col_sizes;
    int **lists = levelOrder(&root, &count, &col_sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}
