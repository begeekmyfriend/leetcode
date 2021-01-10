#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    struct ListNode *p;
    for (p = headA; p->next != NULL; p = p->next) {}
    p->next = headB;

    struct ListNode *slow = headA, *fast = headA;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = headA;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            p->next = NULL;
            return slow;
        }
    }

    p->next = NULL;
    return NULL;
}

int main(int argc, char **argv)
{
    struct ListNode *headA = malloc(sizeof(*headA));
    struct ListNode *headB = malloc(sizeof(*headB));
    struct ListNode *common = malloc(sizeof(*common));

    headA->val = 1;
    headB->val = 2;
    common->val = 4;
    headA->next = common;
    headB->next = common;
    common->next = NULL;

    struct ListNode *p = getIntersectionNode(headA, headB);
    if (p != NULL) {
        printf("%d\n", p->val);
    }
    return 0;
}
