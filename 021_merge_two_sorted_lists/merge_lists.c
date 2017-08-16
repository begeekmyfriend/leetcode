#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode dummy, *tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL || l2 != NULL) {
        struct ListNode *node = malloc(sizeof(*node));
        node->next = NULL;
        tail->next = node;
        tail = node;
        if (l1 != NULL) {
            if (l2 != NULL) {
                if (l1->val < l2->val) {
                    node->val = l1->val;
                    l1 = l1->next;
                } else {
                    node->val = l2->val;
                    l2 = l2->next;
                }
            } else {
                node->val = l1->val;
                l1 = l1->next;
            }
        } else {
            node->val = l2->val;
            l2 = l2->next;
        }
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
