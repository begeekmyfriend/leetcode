#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
 
static struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    if (n < 1) return NULL;

    struct ListNode *p, *prev, dummy;
    dummy.next = head;
    p = prev = &dummy;
    while (n-- > 0) {
        p = p->next;
    }

    while (p->next != NULL) {
        p = p->next;
        prev = prev->next;
    }

    struct ListNode *tmp = prev->next;
    prev->next = tmp->next;
    if (tmp == head) {
        head = tmp->next;
    }
    return head;
}

int main(int argc, char **argv)
{
    int i;
    struct ListNode *list, *p, *prev = NULL;
    for (i = 1; i < argc; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i]);
        p->next = NULL;
        if (i == 1) {
            list = p;
        }
        if (prev != NULL) {
            prev->next = p;
        }
        prev = p;
    }

    list = removeNthFromEnd(list, 1);
    if (list != NULL) {
        for (p = list; p != NULL; p = p->next) {
            printf("%d\n", p->val);
        }
    }
    
    return 0;
}
