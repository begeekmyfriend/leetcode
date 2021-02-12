#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
         &(pos)->member != (head); \
         pos = list_entry((pos)->member.next, typeof(*pos), member))

struct list_head {
    struct list_head *next, *prev;
};

struct rem_node {
    int key;
    int index;
    struct list_head link;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static inline void list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

static int find(struct list_head *heads, int size, int key)
{
    struct rem_node *node;
    int hash = key % size;
    list_for_each_entry(node, &heads[hash], link) {
        if (key == node->key) {
            return node->index;
        }
    }
    return -1;
}

char* fractionToDecimal(int numerator, int denominator)
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
    struct list_head *heads = malloc(size * sizeof(*heads));
    for (i = 0; i < size; i++) {
        INIT_LIST_HEAD(&heads[i]);
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
        list_add(&node->link, &heads[hash]);

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
