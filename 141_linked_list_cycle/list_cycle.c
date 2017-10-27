#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static bool hasCycle(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return false;
    }

    bool first = true;
    struct ListNode *p0, *p1;
    for (p0 = head, p1 = head; p1 != NULL && p1->next != NULL; p0 = p0->next, p1 = p1->next->next) {
        if (p0 == p1 && !first) {
            return true;
        }
        first = false;
    }

    return false;
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
    p->next = head;

    printf("%s\n", hasCycle(head) ? "true" : "false");
    return 0;
}
