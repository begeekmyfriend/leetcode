#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *recursive(struct ListNode *prev, struct ListNode *p)
{
    if (p == NULL) {
        return prev;
    }

    struct ListNode *q = p->next;
    p->next = prev;
    return recursive(p, q);
}

static struct ListNode *reverseList(struct ListNode *head)
{
    return recursive(NULL, head);
}


/* Iteration */
#if 0
static struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *p = head;
    while (p != NULL) {
        struct ListNode *q = p->next;
        p->next = prev;
        prev = p;
        p = q;
    }

    return prev;
}
#endif

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    struct ListNode *head = NULL, *p, *prev;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 1]);
        p->next = NULL;
        if (head == NULL) {
            head = p;
        } else {
            prev->next = p;
        }
        prev = p;
    }

    for (p = reverseList(head); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
