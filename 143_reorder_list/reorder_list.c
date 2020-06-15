#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static void reorderList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return;
    }

    int count = 0;
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    struct ListNode *p, *q;

    /* locate half length */
    dummy.next = head;
    for (p = head, q = head; q != NULL; q = q->next) {
        if ((++count & 0x1) == 0) {
            prev = p;
            p = p->next;
        }
    }

    /* reverse latter half list */
    while (p->next != NULL) {
        q = p->next;
        /* deletion */
        p->next = q->next;
        /* insertion */
        q->next = prev->next;
        prev->next = q;
    }

    /* insert each element interleavingly */
    struct ListNode *last = prev;
    p = head;
    while (p != last) {
        q = last->next;
        /* deletion */
        last->next = q->next;
        /* insertion */
        q->next = p->next;
        p->next = q;
        p = q->next;
    }
}

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

    reorderList(head);
    for (p = head; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
