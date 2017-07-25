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

static int exist(int **quadruplets, int count, int *q)
{
    int i;
    for (i = 0; i < count; i++) {
        int *quad = quadruplets[i];
        if ((quad[0] == q[0] && quad[1] == q[1] && quad[2] == q[2] && quad[3] == q[3]) ||
            (quad[0] == q[0] && quad[1] == q[1] && quad[2] == q[3] && quad[3] == q[2]) ||
            (quad[0] == q[0] && quad[1] == q[2] && quad[2] == q[1] && quad[3] == q[3]) ||
            (quad[0] == q[0] && quad[1] == q[2] && quad[2] == q[3] && quad[3] == q[1]) ||
            (quad[0] == q[0] && quad[1] == q[3] && quad[2] == q[1] && quad[3] == q[2]) ||
            (quad[0] == q[0] && quad[1] == q[3] && quad[2] == q[2] && quad[3] == q[1]) ||
            (quad[0] == q[1] && quad[1] == q[0] && quad[2] == q[2] && quad[3] == q[3]) ||
            (quad[0] == q[1] && quad[1] == q[0] && quad[2] == q[3] && quad[3] == q[2]) ||
            (quad[0] == q[1] && quad[1] == q[2] && quad[2] == q[0] && quad[3] == q[3]) ||
            (quad[0] == q[1] && quad[1] == q[2] && quad[2] == q[3] && quad[3] == q[0]) ||
            (quad[0] == q[1] && quad[1] == q[3] && quad[2] == q[0] && quad[3] == q[2]) ||
            (quad[0] == q[1] && quad[1] == q[3] && quad[2] == q[2] && quad[3] == q[0]) ||
            (quad[0] == q[2] && quad[1] == q[0] && quad[2] == q[1] && quad[3] == q[3]) ||
            (quad[0] == q[2] && quad[1] == q[0] && quad[2] == q[3] && quad[3] == q[1]) ||
            (quad[0] == q[2] && quad[1] == q[1] && quad[2] == q[0] && quad[3] == q[3]) ||
            (quad[0] == q[2] && quad[1] == q[1] && quad[2] == q[3] && quad[3] == q[0]) ||
            (quad[0] == q[2] && quad[1] == q[3] && quad[2] == q[0] && quad[3] == q[1]) ||
            (quad[0] == q[2] && quad[1] == q[3] && quad[2] == q[1] && quad[3] == q[0]) ||
            (quad[0] == q[3] && quad[1] == q[0] && quad[2] == q[1] && quad[3] == q[2]) ||
            (quad[0] == q[3] && quad[1] == q[0] && quad[2] == q[2] && quad[3] == q[1]) ||
            (quad[0] == q[3] && quad[1] == q[1] && quad[2] == q[0] && quad[3] == q[2]) ||
            (quad[0] == q[3] && quad[1] == q[1] && quad[2] == q[2] && quad[3] == q[0]) ||
            (quad[0] == q[3] && quad[1] == q[2] && quad[2] == q[0] && quad[3] == q[1]) ||
            (quad[0] == q[3] && quad[1] == q[2] && quad[2] == q[1] && quad[3] == q[0])) {
            return 1;
        }
    }
    return 0;
}

/**
 *  * Return an array of arrays of size *returnSize.
 *   * Note: The returned array must be malloced, assume caller calls free().
 *    */
static int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
    struct hash_table {
        struct hlist_head head;
    };
    struct element {
        int index;
        int num;
        struct hlist_node node;
    };

    if (numsSize < 4) {
        return NULL;
    }

    int i, j, k, count = 0, cap = 1;
    int **results = malloc(cap * sizeof(int *));
    struct hash_table *ht = malloc(numsSize * sizeof(*ht));
    for (i = 0; i < numsSize; i++) {
        INIT_HLIST_HEAD(&ht[i].head);
    }

    struct element *elems = malloc(numsSize * sizeof(*elems));
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

    for (i = 0; i < numsSize - 1; i++) {
        for (j = i + 1; j < numsSize; j++) {
            int new_target = target - nums[i] - nums[j];
            for (k = j + 1; k < numsSize; k++) {
                int other = new_target - nums[k];
                int hash = other < 0 ? -other % numsSize : other % numsSize;
                int index = -1;
                struct hlist_node *pos;

                hlist_for_each(pos, &ht[hash].head) {
                    struct element *elem = hlist_entry(pos, struct element, node);
                    if (elem->num == other) {
                        /* Eliminate duplicate */
                        if (elem->index > k) {
                            index = elem->index;
                            break;
                        }
                    }    
                }

                if (index >= 0) {
                    int *quadruplet = malloc(4 * sizeof(int));
                    quadruplet[0] = nums[i];
                    quadruplet[1] = nums[j];
                    quadruplet[2] = nums[k];
                    quadruplet[3] = nums[index];
                    if (!exist(results, count, quadruplet)) {
                        if (count + 1 >= cap) {
                            cap *= 2;
                            results = realloc(results, cap * sizeof(int *));
                        }
                        results[count++] = quadruplet;
                    } else {
                        free(quadruplet);
                    }
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
    //int nums[] = { 1, 0, -1, 0, -2, 2 };
    //int nums[] = { -3, -2, -1, 0, 0, 1, 2, 3 };
    int nums[] = { 0, 1, 5, 0, 1, 5, 5, -4 };
    int **quadruplets = fourSum(nums, sizeof(nums) / sizeof(nums[0]), 11, &count);
    for (i = 0; i < count; i++) {
        printf("%d %d %d %d\n", quadruplets[i][0], quadruplets[i][1], quadruplets[i][2], quadruplets[i][3]);
    }

    return 0;
}
