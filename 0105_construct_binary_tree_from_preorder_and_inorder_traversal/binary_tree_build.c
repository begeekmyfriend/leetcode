#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

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

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct order_node {
    struct hlist_node node;
    int val;
    int index;
};

static int find(int num, int size, struct hlist_head *heads)
{
    struct hlist_node *p;
    int hash = (num < 0 ? -num : num) % size;
    hlist_for_each(p, &heads[hash]) {
        struct order_node *on = list_entry(p, struct order_node, node);
        if (num == on->val) {
            return on->index;
        }
    }
    return -1;
}

static struct TreeNode *node_new(int val)
{
    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = val;
    tn->left = NULL;
    tn->right = NULL;
    return tn;
}

static struct TreeNode *dfs(int *preorder, int pre_low, int pre_high, int *inorder,
                            int in_low, int in_high, struct hlist_head *in_heads, int size)
{
    if (in_low > in_high || pre_low > pre_high) {
        return NULL;
    }
    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = preorder[pre_low];
    int index = find(preorder[pre_low], size, in_heads);
    tn->left = dfs(preorder, pre_low + 1, pre_low + (index - in_low), inorder, in_low, index - 1, in_heads, size);
    tn->right = dfs(preorder, pre_high - (in_high - index - 1), pre_high, inorder, index + 1, in_high, in_heads, size);
    return tn;
}

static void node_add(int val, int index, int size, struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->index = index;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

static struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    int i, j;
    struct hlist_head *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (i = 0; i < inorderSize; i++) {
        INIT_HLIST_HEAD(&in_heads[i]);
    }
    for (i = 0; i < inorderSize; i++) {
        node_add(inorder[i], i, inorderSize, in_heads);
    }

    return dfs(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1, in_heads, inorderSize);
}

static void dump(struct TreeNode *node)
{
    if (node == NULL) {
        printf("# ");
        return;
    }
    printf("%d ", node->val);
    dump(node->left);
    dump(node->right);
}

int main(void)
{
    //int preorder[] = { 8,4,2,1,3,6,5,7,12,10,9,11,14,13,15 };
    //int inorder[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    int preorder[] = { 7,-10,-4,3,-1,2,-8,11 };
    int inorder[] = { -4,-10,3,-1,7,11,-8,2 };
    //int preorder[] = { 3,2,1 };
    //int preorder[] = { 3,1,2 };
    //int preorder[] = { 2,1,3 };
    //int preorder[] = { 1,3,2 };
    //int preorder[] = { 1,2,3 };
    //int inorder[] = { 1,2,3 };
    int pre_size = sizeof(preorder) / sizeof(*preorder);
    int in_size = sizeof(inorder) / sizeof(*inorder);
    struct TreeNode *root = buildTree(preorder, pre_size, inorder, in_size);
    dump(root);
    printf("\n");
    return 0;
}
