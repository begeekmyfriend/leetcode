#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummy, *p, *prev, *next;
    if (head == NULL) {
        return NULL;
    }
    dummy.next = head;
    prev = &dummy;
    p = dummy.next;
    next = p->next;
    while (p != NULL && next != NULL) {
        prev->next = next;
        p->next = next->next;
        next->next = p;
        prev = p;
        p = p->next;
        if (p != NULL) {
           next = p->next;
        }
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
