#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    int len = n - m + 1;
    if (len == 1) {
        return head;
    }

    struct ListNode dummy;
    struct ListNode *p = head;
    struct ListNode *prev = &dummy;
    prev->next = p;
    while (--m > 0) {
        prev = p;
        p = p->next;
    }

    struct ListNode *q = p->next;
    while (--len > 0) {
        p->next = q->next;
        q->next = prev->next;
        prev->next = q;
        q = p->next;
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test m n 1 2 3...\n");
        exit(-1);
    }
    int i, count = argc - 3;
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    struct ListNode *p;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 3]);
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    struct ListNode *head = reverseBetween(dummy.next, m, n);
    for (p = head; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
