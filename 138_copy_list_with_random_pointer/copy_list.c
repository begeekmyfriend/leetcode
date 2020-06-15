#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

static struct Node *copyRandomList(struct Node *head)
{
    if (head == NULL) {
        return NULL;
    }

    /* copy and redirect next pointer */
    struct Node *p, *new;
    for (p = head; p != NULL; p = p->next->next) {
        new = malloc(sizeof(*new));
        new->val = p->val;
        new->next = p->next;
        p->next = new;
    }

    /* clone random pointer */
    for (p = head; p != NULL; p = p->next->next) {
        new = p->next;
        new->random = p->random != NULL ? p->random->next : NULL;
    }

    struct Node dummy;
    struct Node *prev = &dummy;
    for (p = head; p != NULL; p = p->next) {
        new = p->next;
        p->next = new->next;
        /* correct the actual next pointer of the new list */
        prev->next = new;
        prev = new;
        new->next = NULL;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    struct Node *head = NULL, *p, *prev;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 1]);
        p->next = NULL;
        p->random = NULL;
        if (head == NULL) {
            head = p;
        } else {
            prev->next = p;
            prev->random = p;
        }
        prev = p;
    }

    struct Node *r = head;
    struct Node *q = p = copyRandomList(head);

    for (r = head; r != NULL; r = r->next) {
        printf("%d ", r->val);
    }
    printf("\n");

    for (r = head; r != NULL; r = r->random) {
        printf("%d ", r->val);
    }
    printf("\n");

    for (; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");

    for (; q != NULL; q = q->random) {
        printf("%d ", q->val);
    }
    printf("\n");
    return 0;
}
