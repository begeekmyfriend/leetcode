#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode dummy;
    struct ListNode *tail = &dummy;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 != NULL ? l1 : l2;

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
