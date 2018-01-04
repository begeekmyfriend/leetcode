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
    struct hlist_node *next, **prev;
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
        h->first->prev = &n->next;
    }
    n->next = h->first;
    n->prev = &h->first;
    h->first = n;
}

static inline void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **prev = n->prev;
    *prev = next;
    if (next != NULL) {
        next->prev = prev;
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

static void node_add(int val, int index, int size, struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->index = index;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

static struct TreeNode *dfs(int *inorder, int in_low, int in_high, int *postorder,
                            int post_low, int post_high, struct hlist_head *in_heads, int size)
{
    if (in_low > in_high || post_low > post_high) {
        return NULL;
    }
    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = postorder[post_high];
    int index = find(postorder[post_high], size, in_heads);
    tn->left = dfs(inorder, in_low, index - 1, postorder, post_low, post_low + (index - 1 - in_low), in_heads, size);
    tn->right = dfs(inorder, index + 1, in_high, postorder, post_high - (in_high - index), post_high - 1, in_heads, size);
    return tn;
}

static struct TreeNode *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize)
{
    int i, j;
    struct hlist_head *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (i = 0; i < inorderSize; i++) {
        INIT_HLIST_HEAD(&in_heads[i]);
    }
    for (i = 0; i < inorderSize; i++) {
        node_add(inorder[i], i, inorderSize, in_heads);
    }

    return dfs(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1, in_heads, inorderSize);
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
    //int postorder[] = { 1,2,3 };
    //int postorder[] = { 2,1,3 };
    //int postorder[] = { 1,3,2 };
    //int postorder[] = { 2,3,1 };
    int postorder[] = { 3,2,1 };
    int inorder[] = { 1,2,3 };
    int post_size = sizeof(postorder) / sizeof(*postorder);
    int in_size = sizeof(inorder) / sizeof(*inorder);
    struct TreeNode *root = buildTree(inorder, in_size, postorder, post_size);
    dump(root);
    printf("\n");
    return 0;
}
