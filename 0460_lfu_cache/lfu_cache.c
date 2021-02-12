#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member), \
         n = list_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

struct list_head {
    struct list_head *next, *prev;
};

typedef struct FreqAVLNode {
    int freq;
    int height;
    struct FreqAVLNode *children[2];
    struct FreqAVLNode *parent;
    struct list_head dhead;     /* freq_list head */
} FreqAVLNode;

typedef struct {
    FreqAVLNode *root;
    FreqAVLNode *min_freq_node;
} FreqAVLTree;

typedef struct LFUNode {
    int key;
    int val;
    int freq;
    FreqAVLNode *node;          /* freq tree node */
    struct list_head dlink;     /* freq_list */
    struct list_head key_link;  /* key_map */
} LFUNode;

typedef struct {
    int size;
    int capacity;
    FreqAVLTree *tree;
    struct list_head hheads[0];
} LFUCache;

static inline void
INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int
list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline void
__list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void
list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static inline void
list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

static inline void
__list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static inline void
list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

static inline int height(FreqAVLNode *node)
{
    return node != NULL ? node->height : 0;
}

static inline void avl_update_height(FreqAVLNode *node)
{
    int ld = height(node->children[0]);
    int rd = height(node->children[1]);
    node->height = 1 + (ld > rd ? ld : rd);
}

static void avl_node_replace(FreqAVLTree *tree, FreqAVLNode *old, FreqAVLNode *new)
{
    if (new != NULL) {
        new->parent = old->parent;
    }

    FreqAVLNode *parent = old->parent;
    if (parent == NULL) {
        tree->root = new;
    } else {
        if (parent->children[0] == old) {
            parent->children[0] = new;
        } else {
            parent->children[1] = new;
        }
        avl_update_height(parent);
    }
}

static FreqAVLNode *avl_node_rotate(FreqAVLTree *tree, FreqAVLNode *node, int side)
{
    /* The child of this node will take its place:
       for a left rotation, it is the right child, and vice versa. */
    FreqAVLNode *new = node->children[1 - side];

    /* Make new the root, rearrange pointers */
    avl_node_replace(tree, node, new);
    node->children[1 - side] = new->children[side];
    new->children[side] = node;

    /* Update parent references */
    node->parent = new;
    if (node->children[1 - side] != NULL) {
        node->children[1 - side]->parent = node;
    }

    /* Update heights of the affected nodes */
    avl_update_height(new);
    avl_update_height(node);

    return new;
}

static FreqAVLNode *avl_node_balance(FreqAVLTree *tree, FreqAVLNode *node)
{
    FreqAVLNode *left = node->children[0];
    FreqAVLNode *right = node->children[1];

    int diff = height(left) - height(right);
    if (diff <= -2) {
        /* Biased toward the right side */
        if (height(right->children[0]) > height(right->children[1])) {
            /* double rotation: at node->right->left */
            avl_node_rotate(tree, right, 1);
        }
        /* single rotation: at node->right->right */
        node = avl_node_rotate(tree, node, 0);
    } else if (diff >= 2) {
        /* Biased toward the left side */
        if (height(left->children[0]) < height(left->children[1])) {
            /* double rotation: at node->left->right */
            avl_node_rotate(tree, left, 0);
        }
        /* single rotation: at node->left->left */
        node = avl_node_rotate(tree, node, 1);
    }

    avl_update_height(node);
    return node;
}

static void avl_tree_balance(FreqAVLTree *tree, FreqAVLNode *node)
{
    while (node != NULL) {
        node = avl_node_balance(tree, node);
        node = node->parent;
    }
}

static FreqAVLNode *avl_tree_insert(FreqAVLTree *tree, int freq)
{
    /* Walk down the tree until we reach a NULL pointer */
    FreqAVLNode *parent = NULL;
    FreqAVLNode **rover = &tree->root;
    while (*rover != NULL) {
        parent = *rover;
        if (freq < (*rover)->freq) {
            rover = &((*rover)->children[0]);
        } else if (freq > (*rover)->freq) {
            rover = &((*rover)->children[1]);
        } else {
            return *rover;
        }
    }

    /* Create a new node and insert into parent's children link */
    FreqAVLNode *node = malloc(sizeof(*node));
    INIT_LIST_HEAD(&node->dhead);
    node->children[0] = NULL;
    node->children[1] = NULL;
    node->parent = parent;
    node->freq = freq;
    node->height = 1;

    /* Insert at parent's children link (assign the children pointer value) */
    *rover = node;
    /* Rebalance the tree */
    avl_tree_balance(tree, parent);
    return node;
}

static FreqAVLNode *avl_node_closest_get(FreqAVLTree *tree, FreqAVLNode *node)
{
    FreqAVLNode *left = node->children[0];
    FreqAVLNode *right = node->children[1];
    if (left == NULL && right == NULL) {
        /* return NULL if leaf node */
        return NULL;
    }

    /* Search down the tree, back towards the center. */
    int side = height(left) > height(right) ? 0 : 1;
    FreqAVLNode *closest = node->children[side];
    while (closest->children[1 - side] != NULL) {
        closest = closest->children[1 - side];
    }

    /* Unlink the closest node, and hook in its remaining child
     * (if it has one) to replace it. */
    avl_node_replace(tree, closest, closest->children[side]);

    /* Update the subtree height for the closest node's old parent. */
    avl_update_height(closest->parent);
    return closest;
}

static void avl_node_erase(FreqAVLTree *tree, FreqAVLNode *node)
{
    /* The node to be erased must be swapped with an "adjacent" node, ie.
     * one which has the closest key to this one. Find the node to swap with. */
    FreqAVLNode *startpoint;
    FreqAVLNode *swap_node = avl_node_closest_get(tree, node);
    if (swap_node == NULL) {
        /* This is a leaf node and has no children, therefore
         * it can be immediately erased. */
        avl_node_replace(tree, node, NULL);
        /* Start rebalancing from the parent of the original node */
        startpoint = node->parent;
    } else {
        /* We will start rebalancing from the old parent of the swap node.
         * Sometimes, the old parent is the node we are removing,
         * in which case we must start rebalancing from the swap node. */
        if (swap_node->parent == node) {
            startpoint = swap_node;
        } else {
            startpoint = swap_node->parent;
        }

        /* Copy references */
        int i;
        for (i = 0; i < 2; i++) {
            swap_node->children[i] = node->children[i];
            if (swap_node->children[i] != NULL) {
                swap_node->children[i]->parent = swap_node;
            }
        }

        swap_node->height = node->height;
        /* Link the parent's reference to this node */
        avl_node_replace(tree, node, swap_node);
    }

    free(node);

    /* Rebalance the tree */
    avl_tree_balance(tree, startpoint);
}

static FreqAVLTree *avl_tree_init(void)
{
    FreqAVLTree *tree = malloc(sizeof(*tree));
    tree->root = NULL;
    tree->min_freq_node = NULL;
    return tree;
}

static void avl_node_destory_recursive(FreqAVLNode *root)
{
    if (root == NULL) {
        return;
    }

    avl_node_destory_recursive(root->children[0]);
    avl_node_destory_recursive(root->children[1]);

    free(root);
}

static void avl_tree_destory(FreqAVLTree *tree)
{
    avl_node_destory_recursive(tree->root);
}

static void freq_incr(FreqAVLTree* tree, LFUNode *lfu, int key)
{
    /* New frequency */
    list_del(&lfu->dlink);
    int freq = ++lfu->freq;
    FreqAVLNode *node = avl_tree_insert(tree, freq);
    if (list_empty(&lfu->node->dhead)) {
        if (lfu->node == tree->min_freq_node) {
            tree->min_freq_node = node;
        }
        /* we must erase the empty node to rearrange the AVL tree */
        avl_node_erase(tree, lfu->node);
    }
    lfu->node = node;
    list_add(&lfu->dlink, &lfu->node->dhead);
}

LFUCache* lFUCacheCreate(int capacity)
{
    int i;
    LFUCache* obj = malloc(sizeof(*obj) + capacity * sizeof(struct list_head));
    obj->size = 0;
    obj->capacity = capacity;
    obj->tree = avl_tree_init();
    for (i = 0; i < capacity; i++) {
        INIT_LIST_HEAD(&obj->hheads[i]);
    }
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key)
{
    if (obj->capacity <= 0) {
        return;
    }

    LFUNode *lfu;
    int hash = key % obj->capacity;
    list_for_each_entry(lfu, &obj->hheads[hash], key_link) {
        if (lfu->key == key) {
            freq_incr(obj->tree, lfu, key);
            return lfu->val;
        }
    }
    return -1;
}

void lFUCachePut(LFUCache* obj, int key, int value)
{
    if (obj->capacity <= 0) {
        return;
    }

    LFUNode *lfu;
    int hash = key % obj->capacity;
    list_for_each(lfu, &obj->hheads[hash], key_link) {
        if (lfu->key == key) {
            freq_incr(obj->tree, lfu, key);
            lfu->val = value;
            return;
        }
    }

    /* squeeze minimum frequency */
    if (obj->size == obj->capacity) {
        FreqAVLNode *node = obj->tree->min_freq_node;
        lfu = list_last_entry(&node->dhead, LFUNode, dlink);
        list_del(&lfu->dlink);
        list_del(&lfu->key_link);
        /* NOTE: we DO NOT need to erase the empty AVL node since the min freq node would be update immediately */
    } else {
        /* new LFU */
        obj->size++;
        lfu = malloc(sizeof(*lfu));
    }

    lfu->key = key;
    lfu->val = value;
    lfu->freq = 1;
    lfu->node = avl_tree_insert(obj->tree, lfu->freq);
    obj->tree->min_freq_node = lfu->node;
    list_add(&lfu->dlink, &lfu->node->dhead);
    list_add(&lfu->key_link, &obj->hheads[hash]);
}

void lFUCacheFree(LFUCache* obj)
{
    int i;
    for (i = 0; i < obj->capacity; i++) {
        LFUNode *lfu, *n;
        list_for_each_entry_safe(lfu, n, &obj->hheads[i], key_link) {
            list_del(&lfu->dlink);
            list_del(&lfu->key_link);
            free(lfu);
        }
    }

    avl_tree_destory(obj->tree);
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 
 * lFUCachePut(obj, key, value);
 
 * lFUCacheFree(obj);
*/

int main(void)
{
    LFUCache* obj = lFUCacheCreate(2);
#if 1
    lFUCachePut(obj, 1, 1);
    printf("Put 1 1\n");
    lFUCachePut(obj, 2, 2);
    printf("Put 2 2\n");
    printf("Get 1 %d\n", lFUCacheGet(obj, 1));
    lFUCachePut(obj, 3, 3);
    printf("Put 3 3\n");
    printf("Get 2 %d\n", lFUCacheGet(obj, 2));
    printf("Get 3 %d\n", lFUCacheGet(obj, 3));
    lFUCachePut(obj, 4, 4);
    printf("Put 4 4\n");
    printf("Get 1 %d\n", lFUCacheGet(obj, 1));
    printf("Get 3 %d\n", lFUCacheGet(obj, 3));
    printf("Get 4 %d\n", lFUCacheGet(obj, 4));
#else
    lFUCachePut(obj, 2, 1);
    printf("Put 2 1\n");
    lFUCachePut(obj, 3, 2);
    printf("Put 3 2\n");
    printf("Get 3 %d\n", lFUCacheGet(obj, 3));
    printf("Get 2 %d\n", lFUCacheGet(obj, 2));
    lFUCachePut(obj, 4, 3);
    printf("Put 4 3\n");
    printf("Get 2 %d\n", lFUCacheGet(obj, 2));
    printf("Get 3 %d\n", lFUCacheGet(obj, 3));
    printf("Get 4 %d\n", lFUCacheGet(obj, 4));
#endif
    lFUCacheFree(obj);
    return 0;
}
