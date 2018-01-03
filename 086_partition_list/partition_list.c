#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode dummy;
    struct ListNode *p = NULL, *start = &dummy, *pivot;    
    dummy.next = head;
    for (pivot = head; pivot != NULL; pivot = pivot->next) {
        if (pivot->val >= x) {
            /* start->next == pivot */
            break;
        }
        start = pivot;
    }

    struct ListNode *prev;
    for (p = pivot; p != NULL; p = p->next) {
        if (p->val < x) {
            prev->next = p->next;
            p->next = start->next;
            start->next = p;
            start = p;
            p = prev;
        }
        prev = p;
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test target n1 n2 n3...\n");
        exit(-1);
    }

    int i, target = atoi(argv[1]);
    struct ListNode *head = NULL;
    struct ListNode *prev = NULL;
    struct ListNode *p;
    for (i = 0; i < argc - 2; i++) {
        p = malloc(sizeof(*p));
        p->val = atoi(argv[i + 2]);
        p->next = NULL;
        if (head == NULL) {
            head = p;
            prev = head;
        } else {
            prev->next = p;
            prev = p;
        }
    }
    p = partition(head, target);
    while (p != NULL) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
    return 0;
}
