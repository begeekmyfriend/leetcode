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

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct order_node {
    struct list_head link;
    int val;
    int index;
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

static int find(int num, int size, struct list_head *heads)
{
    struct order_node *on;
    int hash = (num < 0 ? -num : num) % size;
    list_for_each_entry(on, &heads[hash], link) {
        if (num == on->val) {
            return on->index;
        }
    }
    return -1;
}

static void node_add(int val, int index, int size, struct list_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->index = index;
    int hash = (val < 0 ? -val : val) % size;
    list_add(&on->link, &heads[hash]);
}

static struct TreeNode *dfs(int *inorder, int in_lo, int in_hi, int *postorder,
                            int post_lo, int post_hi, struct list_head *in_heads, int size)
{
    if (in_lo > in_hi || post_lo > post_hi) {
        return NULL;
    }
    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = postorder[post_hi];
    int index = find(postorder[post_hi], size, in_heads);
    tn->left = dfs(inorder, in_lo, index - 1, postorder, post_lo, post_lo + (index - 1 - in_lo), in_heads, size);
    tn->right = dfs(inorder, index + 1, in_hi, postorder, post_hi - (in_hi - index), post_hi - 1, in_heads, size);
    return tn;
}

struct TreeNode *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize)
{
    int i;
    struct list_head *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (i = 0; i < inorderSize; i++) {
        INIT_LIST_HEAD(&in_heads[i]);
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
