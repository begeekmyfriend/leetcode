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

static int exist(int **triplets, int count, int *t)
{
    int i;
    for (i = 0; i < count; i++) {
        int *triplet = triplets[i];
        if ((triplet[0] == t[0] && triplet[1] == t[1] && triplet[2] == t[2]) ||
            (triplet[0] == t[0] && triplet[1] == t[2] && triplet[2] == t[1]) ||
            (triplet[0] == t[1] && triplet[1] == t[0] && triplet[2] == t[2]) ||
            (triplet[0] == t[1] && triplet[1] == t[2] && triplet[2] == t[0]) ||
            (triplet[0] == t[2] && triplet[1] == t[0] && triplet[2] == t[1]) ||
            (triplet[0] == t[2] && triplet[1] == t[1] && triplet[2] == t[0])) {
            return 1;
        }
    }
    return 0;
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** threeSum(int* nums, int numsSize, int* returnSize) {
    struct hash_table {
        struct hlist_head head;
    };
    struct plus_elem {
        int index;
        int num;
        struct hlist_node node;
    };

    if (numsSize < 3) {
        return NULL;
    }

    int i, j, count = 0, cap = 1;
    int **results = malloc(cap * sizeof(int *));
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
        int target = -nums[i];
        for (j = i + 1; j < numsSize; j++) {
            int other = target - nums[j];
            int hash = other < 0 ? -other % numsSize : other % numsSize;
            int index = -1;
            struct hlist_node *pos;

            hlist_for_each(pos, &ht[hash].head) {
                struct plus_elem *elem = hlist_entry(pos, struct plus_elem, node);
                if (elem->num == other) {
                    if (elem->index > j) {
                        index = elem->index;
                        break;
                    }
                }    
            }

            if (index >= 0) {
                int *triplet = malloc(3 * sizeof(int));
                triplet[0] = nums[i];
                triplet[1] = nums[j];
                triplet[2] = nums[index];
                if (!exist(results, count, triplet)) {
                    if (count + 1 >= cap) {
                        cap *= 2;
                        results = realloc(results, cap * sizeof(int *));
                    }
                    results[count++] = triplet;
                } else {
                    free(triplet);
                }
            }
        }
    }

    *returnSize = count;
    return results;
}

int main(void)
{
    int i, count;
    //int nums[] = { -1, 0, 1, 2, -1, -4 };
    int nums[] = { 0, 0, 0 };
    //int nums[] = { -1, 0, 1, 0 };
    int **triplets = threeSum(nums, sizeof(nums) / sizeof(nums[0]), &count);
    for (i = 0; i < count; i++) {
        printf("%d %d %d\n", triplets[i][0], triplets[i][1], triplets[i][2]);
    }

    return 0;
}
