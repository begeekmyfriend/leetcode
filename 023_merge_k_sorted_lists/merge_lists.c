#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct PriorityQueue {
    struct ListNode **nodes;
    int size;
};

static inline void swap(struct ListNode **a, struct ListNode **b)
{
    struct ListNode *tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline int left(int i) { return i * 2 + 1; }
static inline int right(int i) { return left(i) + 1; }
static inline int parent(int i) { return (i - 1) / 2; }

static void queue_dump(struct PriorityQueue *queue)
{
    int i;
    for (i = 0; i < queue->size; i++) {
        printf("%d ", queue->nodes[i]->val);
    }
    printf("\n");
}

static void percolate_up(struct ListNode **nodes, int i)
{
    while (i >= 0 && nodes[parent(i)]->val > nodes[i]->val) {
        swap(nodes + parent(i), nodes + i);
        i = parent(i);
    }
}

static void percolate_down1(struct ListNode **nodes, int size, int child)
{
    int i, min;
    for (i = child; i >= 0; i = parent(i)) {
        if (right(i) < size) {
            min = nodes[left(i)]->val < nodes[right(i)]->val ? left(i) : right(i);
        } else {
            min = left(i);
        }
        if (nodes[min]->val < nodes[i]->val) {
            swap(nodes + min, nodes + i);
        } else {
            break;
        }
    }
}

static void percolate_down2(struct ListNode **nodes, int size)
{
    int i, min;
    for (i = 0; left(i) < size; i = min) {
        if (right(i) < size) {
            min = nodes[left(i)]->val < nodes[right(i)]->val ? left(i) : right(i);
        } else {
            min = left(i);
        }
        if (nodes[min]->val < nodes[i]->val) {
            swap(nodes + min, nodes + i);
        } else {
            break;
        }
    }
}

static void heap_build(struct PriorityQueue *queue)
{
    int i;
    for (i = queue->size / 2 - 1; i > 0; i--) {
        percolate_down1(queue->nodes, queue->size, i);
    }
}

static void put(struct PriorityQueue *queue, struct ListNode *node)
{
    queue->nodes[queue->size++] = node;
    percolate_up(queue->nodes, queue->size - 1);
}

static struct ListNode *get(struct PriorityQueue *queue)
{
    int i;
    struct ListNode *p = queue->nodes[0];
    swap(queue->nodes, queue->nodes + queue->size - 1);
    queue->size--;
    percolate_down2(queue->nodes, queue->size);
    return p;
}

static struct PriorityQueue *init(int size)
{
    struct PriorityQueue *queue = malloc(sizeof(*queue));
    queue->nodes = malloc(size * sizeof(*queue->nodes));
    queue->size = 0;
    return queue;
}

static struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) {
        return NULL;
    }

    if (listsSize == 1) {
        return lists[0];
    }

    int i;
    struct ListNode dummy;
    struct ListNode *prev;
    struct PriorityQueue *queue = init(listsSize);

    dummy.next = NULL;
    prev = &dummy;

    for (i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            put(queue, lists[i]);
        }
    }
    heap_build(queue);

    while (queue->size > 0) {
        struct ListNode *n = get(queue);
        prev->next = n;
        prev = n;
        if (n->next != NULL) {
            put(queue, n->next);
        }
        n->next = NULL;
    }

    return dummy.next;
}

int main(void)
{
    int i, size;
    struct ListNode *p, *prev, *sorted, dummy1, dummy2, **lists;

    dummy1.next = NULL;
    prev = &dummy1;
    for (i = 0; i < 3; i++) {
        p = malloc(sizeof(*p));
        p->val = i * 2;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    for (p = dummy1.next; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    dummy2.next = NULL;
    prev = &dummy2;
    for (i = 0; i < 5; i++) {
        p = malloc(sizeof(*p));
        p->val = i * 2 + 1;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    for (p = dummy2.next; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    size = 2;
    lists = malloc(size * sizeof(struct ListNode *));
    lists[0] = NULL;//dummy1.next;
    lists[1] = NULL;//dummy2.next;
    sorted = mergeKLists(lists, size);
    for (p = sorted; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    return 0;
}
