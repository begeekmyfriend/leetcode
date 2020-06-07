#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    dummy.next = l1;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            prev = l1;
            l1 = l1->next;
        } else {
            struct ListNode *tmp = l2->next;
            l2->next = l1;
            prev->next = l2;
            prev = l2;
            l2 = tmp;
        }
    }

    if (l2 != NULL) {
        prev->next = l2;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    struct ListNode l1;
    l1.val = 2;
    l1.next = NULL;
    struct ListNode l2;
    l2.val = 1;
    l2.next = NULL;
    struct ListNode * list = mergeTwoLists(&l1, &l2);
    while (list != NULL) {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("\n");
    return 0;
}
