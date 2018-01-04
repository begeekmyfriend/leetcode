#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static void reverse(struct ListNode *dummy)
{
    struct ListNode *prev = dummy->next;
    if (prev != NULL) {
        struct ListNode *p = prev->next;
        while (p != NULL) {
            prev->next = p->next;
            p->next = dummy->next;
            dummy->next = p;
            p = prev->next;
        }
    }
}

static void reorderList(struct ListNode *head)
{
    if (head == NULL) {
        return;
    }

    int count = 0;
    struct ListNode *p = head;
    struct ListNode *q = p;

    /* locate half length */
    for (; p != NULL; p = p->next) {
        if ((++count & 0x1) == 0) {
            q = q->next;
        }
    }

    /* reverse latter half list */
    reverse(q);

    /* insert each element */
    struct ListNode *r;
    for (p = head, r = q->next; r != NULL; p = r->next, r = q->next) {
        q->next = r->next;
        r->next = p->next;
        p->next = r;
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
