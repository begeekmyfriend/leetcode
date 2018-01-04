#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static void traverse(struct ListNode *dummy, struct ListNode *end)
{
    if (dummy == NULL || dummy->next == end) {
        return;
    }

    struct ListNode *pivot = dummy->next;
    struct ListNode *prev = pivot;
    struct ListNode *p = pivot->next;
    struct ListNode *first = NULL;

    while (p != end) {
        if (p->val >= pivot->val) {
            if (first == NULL && p->val > pivot->val) {
                first = prev;
            }
            prev = p;
            p = p->next;
        } else {
            prev->next = p->next;
            p->next = dummy->next;
            dummy->next = p;
            p = prev->next;
        }
    }

    traverse(dummy, pivot);
    traverse(first, end);
}

static struct ListNode *sortList(struct ListNode *head)
{
    struct ListNode dummy;
    dummy.next = head;
    traverse(&dummy, NULL);
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

    for (p = sortList(head); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
