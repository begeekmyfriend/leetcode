#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static void recursive(struct ListNode *dummy, struct ListNode *prev, struct ListNode *p)
{
    if (p != NULL) {
        prev->next = p->next;
        p->next = dummy->next;
        dummy->next = p;
        recursive(dummy, prev, prev->next);
    }
}

static struct ListNode *reverseList(struct ListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    struct ListNode dummy;
    dummy.next = head;
    recursive(&dummy, head, head->next);
    return dummy.next;
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

    for (p = reverseList(head); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
