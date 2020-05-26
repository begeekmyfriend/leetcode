#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    int len = 0;
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    dummy.next = head;
    for (; head != NULL; head = head->next) {
        if (++len % k == 0) {
            /* t always the original first one */
            struct ListNode *t = prev->next;
            /* loop condition implicits the final state */
            while (prev->next != head) {
                /* the new segment head */
                struct ListNode *h = t->next;
                /* deletion */
                t->next = h->next;
                /* insertion */
                h->next = prev->next;
                prev->next = h;
            }
            /* For iteration */
            prev = t;
            head = t;
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
    for (i = 2; i < argc; i++) {
        p = malloc(sizeof(*p));
        int n = atoi(argv[i]);
        printf("%d ", n);
        p->val = n;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    putchar('\n');

    list = reverseKGroup(dummy.next, atoi(argv[1]));
    for (p = list; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    return 0;
}
