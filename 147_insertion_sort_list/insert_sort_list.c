#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *insertionSortList(struct ListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    if (head->next == NULL) {
        return head;
    }

    struct ListNode dummy;
    struct ListNode *p0, *p, *p1;
    dummy.next = head;

    for (p0 = head, p = head->next; p != NULL; p0 = p, p = p->next) {
        if (p->val < p0->val) {
            p0->next = p->next;
            for (p1 = &dummy; p1 != p0; p1 = p1->next) {
                if (p1->next->val >= p->val) {
                    p->next = p1->next;
                    p1->next = p;
                    break;
                }
            }
            p = p0;
        }
    }

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

    for (p = insertionSortList(head); p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
