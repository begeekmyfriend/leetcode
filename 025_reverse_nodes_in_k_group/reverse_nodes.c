#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }

    int first = 1;
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *dhead = &dummy;
    struct ListNode *prev = head;
    struct ListNode *p = head->next;
    struct ListNode *next = p == NULL ? NULL : p->next;
    while (p != NULL) {
        int i;
        struct ListNode *end = dhead->next;
        for (i = 0; end != NULL && i < k; i++) {
            end = end->next;
        }
        if (i < k) {
            break;
        }

        while (p != end) {
            p->next = dhead->next;
            dhead->next = p;
            prev->next = next;
            p = next;
            next = p == NULL ? NULL : p->next;
        }

        if (first) {
            first = 0;
            dummy.next = dhead->next;
        }

        dhead = prev;
        prev = p;
        p = p == NULL ? NULL : p->next;
        next = p == NULL ? NULL : p->next;
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
