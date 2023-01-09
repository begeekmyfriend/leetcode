#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


struct ufs {
    int parents[512];
};

static inline void ufs_init(struct ufs *set)
{
    int i;
    for (i = 0; i < sizeof(set->parents) / sizeof(int); i++) {
        set->parents[i] = i;
    }
}

static inline int ufs_find(struct ufs *set, int node)
{
    assert(node >= 0 && node <= sizeof(set->parents) / sizeof(int));
    if (set->parents[node] != node) {
        set->parents[node] = ufs_find(set, set->parents[node]);
    }
    return set->parents[node];
}

static inline void ufs_union(struct ufs *set, int p, int q)
{
    int root_p, root_q;

    root_p = ufs_find(set, p);
    root_q = ufs_find(set, q);
    /* Omit root_p == root_q if-condition */
    set->parents[root_p] = root_q;
}

static inline bool ufs_connected(struct ufs *set, int p, int q)
{
    return ufs_find(set, p) == ufs_find(set, q);
}

bool equationsPossible(char ** equations, int equationsSize)
{
    int i;
    struct ufs *set;

    set = malloc(sizeof(*set));
    ufs_init(set);

    for (i = 0; i < equationsSize; i++) {
        if (equations[i][1] == '=') {
            ufs_union(set, equations[i][0], equations[i][3]);
        }
    }

    for (i = 0; i < equationsSize; i++) {
        if (equations[i][1] == '!') {
            if (ufs_connected(set, equations[i][0], equations[i][3])) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    //char *equations[] = {"a==b", "c==c", "x==y" };
    char *equations[] = {"a==b", "b!=c", "a==c" };
    printf("%s\n", equationsPossible(equations, sizeof(equations)/sizeof(char *)) ? "true" : "false");
    return 0;
}
