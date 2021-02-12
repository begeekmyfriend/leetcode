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

struct seq_node {
    int num;
    struct list_head link;
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

static inline void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

static struct seq_node *find(int num, int size, struct list_head *heads)
{
    struct seq_node *node;
    int hash = num < 0 ? -num % size : num % size;
    list_for_each_entry(node, &heads[hash], link) {
        if (node->num == num) {
            return node;
        }
    }
    return NULL;
}

int longestConsecutive(int* nums, int numsSize)
{
    int i, hash, length = 0;
    struct seq_node *node;
    struct list_head *heads = malloc(numsSize * sizeof(*heads));

    for (i = 0; i < numsSize; i++) {
        INIT_LIST_HEAD(&heads[i]);
    }

    for (i = 0; i < numsSize; i++) {
        if (!find(nums[i], numsSize, heads)) {
            hash = nums[i] < 0 ? -nums[i] % numsSize : nums[i] % numsSize;
            node = malloc(sizeof(*node));
            node->num = nums[i];
            list_add(&node->link, &heads[hash]);
        }
    }

    for (i = 0; i < numsSize; i++) {
        int len = 0;
        int num;
        node = find(nums[i], numsSize, heads);
        while (node != NULL) {
            len++;
            num = node->num;
            list_del(&node->link);

            int left = num;
            while ((node = find(--left, numsSize, heads)) != NULL) {
                len++;
                list_del(&node->link);
            }

            int right = num;
            while ((node = find(++right, numsSize, heads)) != NULL) {
                len++;
                list_del(&node->link);
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
