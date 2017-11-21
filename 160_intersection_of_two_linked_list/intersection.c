#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    struct ListNode *p;
    for (p = headA; p->next != NULL; p = p->next) {}
    p->next = headB;

    bool first = true;
    struct ListNode *p0, *p1;
    for (p0 = headA, p1 = headA; p1 != NULL && p1->next != NULL; p0 = p0->next, p1 = p1->next->next) {
        if (p0 == p1 && !first) {
            p0 = headA;
            while (p0 != p1) {
                p0 = p0->next;
                p1 = p1->next;
            }
            p->next = NULL;
            return p0;
        }
        first = false;
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
