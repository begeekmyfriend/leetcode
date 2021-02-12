#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

struct Point {
    int x, y;
};

struct point_node {
    int p1;
    int p2;
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

static bool can_insert(struct list_head *head, int p1, int p2)
{
    struct point_node *pn;
    list_for_each_entry(pn, head, link) {
        return p1 == pn->p1;
    }
    return true;
}

static int gcd(int x, int y)
{
    while (y != 0) {
        int tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

static int maxPoints(struct Point *points, int pointsSize)
{
    if (pointsSize <= 2) {
        return pointsSize;
    }

    int i, j, slope_size = pointsSize * pointsSize / 2 + 133;
    int *dup_cnts = malloc(pointsSize * sizeof(int));
    int *hori_cnts = malloc(pointsSize * sizeof(int));
    int *vert_cnts = malloc(pointsSize * sizeof(int));
    int *slope_cnts = malloc(slope_size * sizeof(int));
    memset(hori_cnts, 0, pointsSize * sizeof(int));
    memset(vert_cnts, 0, pointsSize * sizeof(int));
    memset(slope_cnts, 0, slope_size * sizeof(int));

    for (i = 0; i < pointsSize; i++) {
        dup_cnts[i] = 1;
    }

    struct list_head *heads = malloc(slope_size * sizeof(*heads));
    for (i = 0; i < slope_size; i++) {
        INIT_LIST_HEAD(&heads[i]);
    }

    for (i = 0; i < pointsSize; i++) {
        for (j = i + 1; j < pointsSize; j++) {
            if (points[i].x == points[j].x) {
                hori_cnts[i]++;
                hori_cnts[j]++;
            }

            if (points[i].y == points[j].y) {
                vert_cnts[i]++;
                vert_cnts[j]++;
            }

            if (points[i].x == points[j].x && points[i].y == points[j].y) {
                dup_cnts[i]++;
                dup_cnts[j]++;
            }

            if (points[i].x != points[j].x && points[i].y != points[j].y) {
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                int tmp = gcd(dx, dy);
                dx /= tmp;
                dy /= tmp;
                int hash = dx * dy - 1333 * (dx + dy);
                if (hash < 0) {
                    hash = -hash;
                }
                hash %= slope_size;
                if (can_insert(&heads[hash], i, j)) {
                    struct point_node *pn = malloc(sizeof(*pn));
                    pn->p1 = i;
                    pn->p2 = j;
                    list_add(&pn->link, &heads[hash]);
                }
            }
        }
    }

    for (i = 0; i < slope_size; i++) {
        int index = -1;
        struct point_node *pn;
        list_for_each_entry(pn, &heads[i], link) {
            index = pn->p1;
            slope_cnts[i]++;
        }
        if (index >= 0) {
            slope_cnts[i] += dup_cnts[index];
        }
    }

    int max_num = 0;
    for (i = 0; i < pointsSize; i++) {
        if (hori_cnts[i] + 1 > max_num) {
            max_num = hori_cnts[i] + 1;
        }
        if (vert_cnts[i] + 1 > max_num) {
            max_num = vert_cnts[i] + 1;
        }
    }
    for (i = 0; i < slope_size; i++) {
        if (slope_cnts[i] > max_num) {
            max_num = slope_cnts[i];
        }
    }

    return max_num;
}

int main(void)
{
#if 0
    struct Point points[4];
    points[0].x = -4;
    points[0].y = 1;
    points[1].x = -7;
    points[1].y = 7;
    points[2].x = -1;
    points[2].y = 5;
    points[3].x = 9;
    points[3].y = -25;
#endif
#if 1
    struct Point points[3];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 94911151;
    points[1].y = 94911150;
    points[2].x = 94911152;
    points[2].y = 94911151;
#endif
#if 0
    struct Point points[9];
    points[0].x = 84;
    points[0].y = 250;
    points[1].x = 0;
    points[1].y = 0;
    points[2].x = 1;
    points[2].y = 0;
    points[3].x = 0;
    points[3].y = -70;
    points[4].x = 0;
    points[4].y = -70;
    points[5].x = 1;
    points[5].y = -1;
    points[6].x = 21;
    points[6].y = 10;
    points[7].x = 42;
    points[7].y = 90;
    points[8].x = -42;
    points[8].y = -230;
#endif
    printf("%d\n", maxPoints(points, sizeof(points) / sizeof(*points)));
    return 0;
}
