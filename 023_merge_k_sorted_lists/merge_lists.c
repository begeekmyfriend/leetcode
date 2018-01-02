#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) {
        return NULL;
    }
    if (listsSize == 1) {
        return lists[0];
    }

    int i, index;
    struct ListNode dummy, *p, *prev;

    dummy.next = NULL;
    prev = &dummy;
    index = 0;
    while (index != -1) {
        int min = INT_MAX;
        index = -1;
        for (i = 0; i < listsSize; i++) {
            if (lists[i] != NULL && lists[i]->val < min) {
                min = lists[i]->val;
                index = i;
            }
        }

        if (index != -1) {
            p = malloc(sizeof(*p));
            p->val = min;
            p->next = NULL;
            prev->next = p;
            prev = p;
            lists[index] = lists[index]->next;
        }
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
