#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    int carry_num = 0;
    int first = 1;
    struct ListNode *res = NULL;
    struct ListNode *p = NULL;
    struct ListNode *prev = p;

    while (l1 != NULL || l2 != NULL || carry_num) {
        int sum = 0;
        int last_carry = carry_num;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        if (sum >= 10) {
            sum -= 10;
            carry_num = 1;
        } else {
            carry_num = 0;
        }

        p = malloc(sizeof(*p));
        if (first) {
             res = p;
             first = 0;
        }
        p->val = sum + last_carry;
        if (p->val >= 10) {
            p->val -= 10;
            carry_num = 1;
        }
        p->next = NULL;
        if (prev != NULL) {
             prev->next = p;
        }
        prev = p;
    }

    return res;
}

static struct ListNode *node_build(const char *digits)
{
    struct ListNode *res, *p, *prev;
    int first = 1;
    int len = strlen(digits);
    const char *c = digits + len - 1;
    prev = NULL;
    while (len-- > 0) {
        p = malloc(sizeof(*p));
        if (first) {
            first = 0;
            res = p;
        }
        p->val = *c-- - '0';
        p->next = NULL;
        if (prev != NULL) {
            prev->next = p;
        }
        prev = p;
    }

    return res;
}

static void show(struct ListNode *ln)
{
    int sum = 0, factor = 1;
    while (ln != NULL) {
        sum += ln->val * factor;
        factor *= 10;
        ln = ln->next;
    }
    printf("%d\n", sum);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test n1 n2\n");
        exit(-1);
    }

    struct ListNode *l1 = node_build(argv[1]);
    struct ListNode *l2 = node_build(argv[2]);
    struct ListNode *res = addTwoNumbers(l1, l2);
    show(l1);
    show(l2);
    show(res);
    return 0;
}
