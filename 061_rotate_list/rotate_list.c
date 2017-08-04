#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy;
    struct ListNode *last = &dummy;
    struct ListNode *p = head;
    int count = k;
    while (k > 0) {
        if (p == NULL) {
            int length = count - k;
            prev = &dummy;
            p = head;
            k = count % length;
            if (k == 0) break;
        }
        prev = p;
        p = p->next;
        k--;
    }

    while (p != NULL) {
        last = last->next;
        prev = p;
        p = p->next;
    }

    if (last != &dummy) {
        prev->next = head;
        dummy.next = last->next;
        last->next = NULL;
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
        printf("%d ", n);
        p->val = n;
        p->next = NULL;
        prev->next = p;
        prev = p;
    }
    putchar('\n');

    list = rotateRight(dummy.next, atoi(argv[1]));
    for (p = list; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    putchar('\n');

    return 0;
}
