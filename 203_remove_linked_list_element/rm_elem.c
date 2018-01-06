#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *removeElement(struct ListNode *head, int val)
{
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy;
    struct ListNode *p = head;
    while (p != NULL) {
        if (p->val == val) {
            prev->next = p->next;
        } else {
            prev = p;
        }
        p = p->next;
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test value n1 n2 n3...\n");
        exit(-1);
    }

    int value = atoi(argv[1]);
    int i, count = argc - 2;
    struct ListNode *head = NULL, *p, *prev;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 2]);
        p->next = NULL;
        if (head == NULL) {
            head = p;
        } else {
            prev->next = p;
        }
        prev = p;
    }

    for (p = removeElement(head, value); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
