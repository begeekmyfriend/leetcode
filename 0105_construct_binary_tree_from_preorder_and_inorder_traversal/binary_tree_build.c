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

static struct TreeNode *dfs(int *preorder, int pre_low, int pre_high, int *inorder,
                            int in_low, int in_high, struct list_head *in_heads, int size)
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

static void node_add(int val, int index, int size, struct list_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->index = index;
    int hash = (val < 0 ? -val : val) % size;
    list_add(&on->link, &heads[hash]);
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    int i;
    struct list_head *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (i = 0; i < inorderSize; i++) {
        INIT_LIST_HEAD(&in_heads[i]);
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
