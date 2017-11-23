#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

static inline void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

static inline int hlist_empty(struct hlist_head *h)
{
    return !h->first;
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first != NULL) {
        h->first->pprev = &n->next;
    }
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

static inline void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next != NULL) {
        next->pprev = pprev;
    }
}

struct rem_node {
    struct hlist_node node;
    int key;
    int index;
};

static int find(struct hlist_head *heads, int size, int key)
{
    int hash = key % size;
    struct hlist_node *pos;
    hlist_for_each(pos, &heads[hash]) {
        struct rem_node *node = list_entry(pos, struct rem_node, node);
        if (key == node->key) {
            return node->index;
        }
    }
    return -1;
}

static char* fractionToDecimal(int numerator, int denominator)
{
    int size = 1024;
    char *result = malloc(size);
    char *p = result;

    if (denominator == 0) {
        result[0] = '\0';
        return result;
    }

    if (numerator == 0) {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    /* using long long type make sure there has no integer overflow */
    long long n = numerator;
    long long d = denominator;

    /* deal with negtive cases */
    if (n < 0) {
        n = -n;
    }
    if (d < 0) {
        d = -d;
    }

    bool sign = (float) numerator / denominator >= 0;
    if (!sign){
        *p++ = '-';
    }

    long long remainder = n % d;
    long long division = n / d;

    sprintf(p, "%ld", division > 0 ? (long) division : (long) -division);
    if (remainder == 0) {
        return result;
    }

    p = result + strlen(result);
    *p++ = '.';

    /* Using a map to record all of reminders and their position.
     * if the reminder appeared before, which means the repeated loop begin,
     */

    int i, j;
    char *decimal = malloc(size);
    memset(decimal, 0, size);
    char *q = decimal;

    size = 1333;
    struct hlist_head *heads = malloc(size * sizeof(*heads));
    for (i = 0; i < size; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    i = 0;
    while (remainder != 0) {
        int pos = find(heads, size, remainder);
        if (pos >= 0) {
            while (pos-- > 0) {
                *p++ = *decimal++;
            }
            *p++ = '(';
            while (*decimal != '\0') {
                *p++ = *decimal++;
            }
            *p++ = ')';
            *p = '\0';
            return result;
        }
        struct rem_node *node = malloc(sizeof(*node));
        node->key = remainder;
        node->index = i;

        int hash = remainder % size;
        hlist_add_head(&node->node, &heads[hash]);

        *q++ = (remainder * 10) / d + '0';
        remainder = (remainder * 10) % d;
        i++;
    }

    strcpy(p, decimal);    
    return result;
}

int main(int argc, char** argv)
{
#if 1
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test numerator denominator\n");
        exit(-1);
    }

    printf("%s\n", fractionToDecimal(atoi(argv[1]), atoi(argv[2])));
#else
    printf("%s\n", fractionToDecimal(1, 6));
    printf("%s\n", fractionToDecimal(100, 6));
    printf("%s\n", fractionToDecimal(-1, 4));
    printf("%s\n", fractionToDecimal(1, -3));
    printf("%s\n", fractionToDecimal(-1, -6));
    printf("%s\n", fractionToDecimal(25, 99));
    printf("%s\n", fractionToDecimal(1, 7));
    printf("%s\n", fractionToDecimal(10, 7));
    printf("%s\n", fractionToDecimal(100, 7));
    printf("%s\n", fractionToDecimal(1, 17));
    printf("%s\n", fractionToDecimal(1, 1024));
    printf("%s\n", fractionToDecimal(-2147483648, -1999));
    printf("%s\n", fractionToDecimal(-1, -2147483648));

#endif
    return 0;
}
