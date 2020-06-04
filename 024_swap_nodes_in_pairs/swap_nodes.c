#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* swapPairs(struct ListNode* head)
{
    if (head == NULL) {
        return NULL;
    }
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy;
    struct ListNode *p = dummy.next;

    while (p != NULL && p->next != NULL) {
        struct ListNode *q = p->next;
        /* deletion */
        p->next = q->next;
        /* insertion */
        q->next = p;
        prev->next = q;
        /* iteration */
        prev = p;
        p = p->next;
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    int i;
    struct ListNode *p, *prev, dummy, *list;

    dummy.next = NULL;
    prev = &dummy;
    for (i = 1; i < argc; i++) {
        p = malloc(sizeof(*p));
        int n = atoi(argv[i]);
        printf("%d ", n);
        p->val = n;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    putchar('\n');

    list = swapPairs(dummy.next);
    for (p = list; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    return 0;
}
