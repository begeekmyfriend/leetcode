#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define BST_MAX_LEVEL   800
#define BST_LEFT_INDEX  0
#define BST_RIGHT_INDEX 1

struct node_backlog {
    /* Node backlogged */
    struct TreeNode *node;
    /* The index next to the backtrack point, valid when >= 1 */
    int next_sub_idx;
};

static inline void
nbl_push(struct node_backlog *nbl, struct node_backlog **top, struct node_backlog **bottom)
{
    if (*top - *bottom < BST_MAX_LEVEL) {
        (*(*top)++) = *nbl;
    }
}

static inline struct node_backlog *
nbl_pop(struct node_backlog **top, struct node_backlog **bottom)
{
    return *top > *bottom ? --*top : NULL;
}

static inline int
is_leaf(struct TreeNode *node)
{
    return node->left == NULL && node->right == NULL;
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize)
{
    int i, j, capacity[BST_MAX_LEVEL];
    int **results = malloc(BST_MAX_LEVEL * sizeof(int *));
    *columnSizes = malloc(BST_MAX_LEVEL * sizeof(int));
    memset(results, 0, BST_MAX_LEVEL * sizeof(int *));
    memset(*columnSizes, 0, BST_MAX_LEVEL * sizeof(int));
    for (i = 0; i < BST_MAX_LEVEL; i++) {
        capacity[i] = 1;
    }

    for (i = 0; i < BST_MAX_LEVEL; i++) {
        int level = 0;
        struct TreeNode *node = root;
        struct node_backlog nbl, *p_nbl = NULL;
        struct node_backlog *top, *bottom, nbl_stack[BST_MAX_LEVEL];

        top = bottom = nbl_stack;

        for (; ;) {
            if (node != NULL) {
                /* Fetch the pop-up backlogged node's sub-id.
                 * If not backlogged, fetch the first sub-id. */
                int sub_index = p_nbl != NULL ? p_nbl->next_sub_idx : BST_LEFT_INDEX;

                /* Draw lines as long as sub_idx is the first one */
                if (sub_index == BST_LEFT_INDEX && level == i) {
                    if (results[i] == NULL) {
                        results[i] = malloc(capacity[i] * sizeof(int));
                    }
                    if ((*columnSizes)[i] + 1 > capacity[i]) {
                        int *p = malloc(capacity[i] * 2 * sizeof(int));
                        memcpy(p, results[i], capacity[i] * sizeof(int));
                        capacity[i] *= 2;
                        free(results[i]);
                        results[i] = p;
                    }
                    results[i][(*columnSizes)[i]++] = node->val;
                }

                /* backlog should be reset since node has gone deep down */
                p_nbl = NULL;

                /* Backlog the node */
                if (is_leaf(node) || sub_index == BST_RIGHT_INDEX) {
                    nbl.node = NULL;
                    nbl.next_sub_idx = BST_LEFT_INDEX;
                } else {
                    nbl.node = node;
                    nbl.next_sub_idx = BST_RIGHT_INDEX;
                }
                nbl_push(&nbl, &top, &bottom);
                level++;

                /* Move down according to sub_idx */
                node = sub_index == BST_LEFT_INDEX ? node->left : node->right;
            } else {
                p_nbl = nbl_pop(&top, &bottom);
                if (p_nbl == NULL) {
                    /* End of traversal */
                    break;
                }
                node = p_nbl->node;
                level--;
            }
        }

        if ((*columnSizes)[i] == 0) {
            break;
        }
    }

    *returnSize = i;
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

    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    int i, j, count = 0, *col_sizes;
    int **lists = levelOrder(&root, &col_sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}
