#include <stdio.h>
#include <stdlib.h>

struct RandomListNode {
    int label;
    struct RandomListNode *next;
    struct RandomListNode *random;
};

static struct RandomListNode *copyRandomList(struct RandomListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    struct RandomListNode *p, *new;
    for (p = head; p != NULL; p = p->next->next) {
        new = malloc(sizeof(*new));
        new->label = p->label;
        new->next = p->next;
        p->next = new;
    }

    for (p = head; p != NULL; p = p->next->next) {
        new = p->next;
        new->random = p->random != NULL ? p->random->next : NULL;
    }

    struct RandomListNode dummy;
    struct RandomListNode *prev = &dummy;
    for (p = head; p != NULL; p = p->next) {
        new = p->next;
        p->next = new->next;
        prev->next = new;
        prev = new;
        new->next = NULL;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    struct RandomListNode *head = NULL, *p, *prev;
    for (i = 0; i < count; i++) {
        p = malloc(sizeof(*p));
        p->label = atoi(argv[i + 1]);
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

    struct RandomListNode *r = head;
    struct RandomListNode *q = p = copyRandomList(head);

    for (r = head; r != NULL; r = r->next) {
        printf("%d ", r->label);
    }
    printf("\n");

    for (r = head; r != NULL; r = r->random) {
        printf("%d ", r->label);
    }
    printf("\n");

    for (; p != NULL; p = p->next) {
        printf("%d ", p->label);
    }
    printf("\n");

    for (; q != NULL; q = q->random) {
        printf("%d ", q->label);
    }
    printf("\n");
    return 0;
}
