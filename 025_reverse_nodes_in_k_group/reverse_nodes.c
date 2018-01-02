#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    int i, len = 0;
    struct ListNode dummy;
    struct ListNode *p = head;
    struct ListNode *prev = &dummy;
    dummy.next = head;
    for (p = head; p != NULL; p = p->next) {
        if (++len % k == 0) {
            struct ListNode *begin = prev->next;
            for (i = 1; i < k; i++) {
                struct ListNode *next = begin->next;
                begin->next = next->next;
                next->next = prev->next;
                prev->next = next;
            }
            p = begin;
            prev = p;
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
