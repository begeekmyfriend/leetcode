#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

static inline void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

static inline int hlist_empty(struct hlist_head *h)
{
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

struct seq_node {
    int num;
    struct hlist_node node;
};

static struct seq_node *find(int num, int size, struct hlist_head *heads)
{
    int hash = num < 0 ? -num % size : num % size;
    struct hlist_node *pos;
    hlist_for_each(pos, &heads[hash]) {
        struct seq_node *node = list_entry(pos, struct seq_node, node);
        if (node->num == num) {
            return node;
        }
    }
    return NULL;
}

static int longestConsecutive(int* nums, int numsSize)
{
    int i, hash, length = 0;
    struct seq_node *node;
    struct hlist_head *heads = malloc(numsSize * sizeof(*heads));

    for (i = 0; i < numsSize; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    for (i = 0; i < numsSize; i++) {
        if (!find(nums[i], numsSize, heads)) {
            hash = nums[i] < 0 ? -nums[i] % numsSize : nums[i] % numsSize;
            node = malloc(sizeof(*node));
            node->num = nums[i];
            hlist_add_head(&node->node, &heads[hash]);
        }
    }

    for (i = 0; i < numsSize; i++) {
        int len = 0;
        int num;
        node = find(nums[i], numsSize, heads);
        while (node != NULL) {
            len++;
            num = node->num;
            hlist_del(&node->node);

            int left = num;
            while ((node = find(--left, numsSize, heads)) != NULL) {
                len++;
                hlist_del(&node->node);
            }

            int right = num;
            while ((node = find(++right, numsSize, heads)) != NULL) {
                len++;
                hlist_del(&node->node);
            }

            length = len > length ? len : length;
        }
    }

    return length;
}

int main(int argc, char **argv)
{
    int i, size = argc - 1;
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", longestConsecutive(nums, size));
    return 0;
}
