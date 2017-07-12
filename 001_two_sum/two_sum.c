#include <stdio.h>
#include <stdlib.h>

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

static inline void INIT_HLIST_NODE(struct hlist_node *n) {
    n->next = NULL;
    n->pprev = NULL;
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

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define hlist_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

static int * twosum(int *nums, int numsSize, int target)
{
    struct hash_table {
        struct hlist_head head;
    };
    struct plus_elem {
        int index;
        int num;
        struct hlist_node node;
    };

    if (numSize < 2) {
        return NULL;
    }

    int i, j;
    struct hash_table *ht = malloc(numsSize * sizeof(*ht));
    for (i = 0; i < numsSize; i++) {
        INIT_HLIST_HEAD(&ht[i].head);
    }

    struct plus_elem *elems = malloc(numsSize * sizeof(*elems));
    for (i = 0; i < numsSize; i++) {
        elems[i].num = 0;
        INIT_HLIST_NODE(&elems[i].node);
    }

    for (i = 0; i < numsSize; i++) {
        int num = nums[i] < 0 ? -nums[i] : nums[i];
        int hash = num % numsSize;
        elems[i].index = i;
        elems[i].num = nums[i];
        hlist_add_head(&elems[i].node, &ht[hash].head);
    }

    for (i = 0; i < numsSize; i++) {
        int other = target - nums[i];
        int h1 = nums[i] < 0 ? -nums[i] % numsSize : nums[i] % numsSize;
        int hash = other < 0 ? -other % numsSize : other % numsSize;
        int index = -1;
        struct hlist_node *pos;

        hlist_for_each(pos, &ht[hash].head) {
            struct plus_elem *elem = hlist_entry(pos, struct plus_elem, node);
            if (elem->num == other) {
                if (elem->index != i) {
                    index = elem->index;
                    break;
                }
            }
        }

        if (index >= 0) {
            int *indexes = malloc(2 * sizeof(int));
            if (indexes == NULL) {
                break;
            }
            indexes[0] = i < index ? i : index;
            indexes[1] = i > index ? i : index;
            return indexes;
        }
    }

    return NULL;
}

int main(void)
{
    //int nums[] = {-1, -2, -3, -4, -5};
    //int target = -8;
    //int nums[] = {0,4,3,0};
    //int target = 0;
    int nums[] = { 3, 2, 4 };
    int target = 6;
    int *indexes = twosum(nums, sizeof(nums) / sizeof(nums[0]), target);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}
