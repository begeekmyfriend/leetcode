#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* rotateRight(struct ListNode* head, int k)
{
    if (head == NULL || k <= 0) {
        return head;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy;
    struct ListNode *p = head;
    int len = 0;
    while (p != NULL) {
        prev = p;
        p = p->next;
        len++;
    }

    struct ListNode *last = prev;
    prev = &dummy;
    p = head;
    len = len - (k % len);
    while (len-- > 0) {
        prev = p;
        p = p->next;
    }

    if (p != NULL) {
        /* deletion */
        prev->next = NULL;
        /* insertion */
        last->next = dummy.next;
        dummy.next = p;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int i;
    struct ListNode *p, *prev, dummy, *list;

    if (argc < 2) {
        fprintf(stderr, "Usage: ./test k n1 n2...\n");
        exit(-1);
    }

    dummy.next = NULL;
    prev = &dummy;
    for (i = 2; i < argc; i++) {
        p = malloc(sizeof(*p));
        int n = atoi(argv[i]);
        p->val = n;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }

    list = rotateRight(dummy.next, atoi(argv[1]));
    for (p = list; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    return 0;
}
