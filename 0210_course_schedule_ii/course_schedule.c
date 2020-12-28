#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct graph_node {
    int req_num;
    int reqs[15];
    bool touched;
    bool taken;
};

static bool dfs(struct graph_node *courses, int id, int *order, int *count)
{
    int i;
    if (courses[id].touched) {
        return true;
    } else if (courses[id].taken) {
        return false;
    } else {
        courses[id].taken = true;
        for (i = 0; i < courses[id].req_num; i++) {
            if (!dfs(courses, courses[id].reqs[i], order, count)) {
                return false;
            }
        }
        /* Record path in backtrace before DFS return */
        order[(*count)++] = id;
        /* If paths overlapped, mark in backtracing for no need to traverse next time */
        courses[id].touched = true;
        courses[id].taken = false;
        return true;
    }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
static int *findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize)
{
    int i;
    int *order = malloc(numCourses * sizeof(int));
    struct graph_node *courses = malloc(numCourses * sizeof(*courses));

    memset(courses, 0, numCourses * sizeof(*courses));
    for (i = 0; i < prerequisitesSize; i++) {
        int id = prerequisites[i][0];
        int req = prerequisites[i][1];
        courses[id].reqs[courses[id].req_num++] = req;
    }

    *returnSize = 0;
    for (i = 0; i < numCourses; i++) {
        if (!dfs(courses, i, order, returnSize)) {
            *returnSize = 0;
            return order;
        }
    }

    return order;
}

int main(void)
{
    int i, course_num = 3, pair_num = 1;
    int **pairs = malloc(pair_num * sizeof(int *));
    int *col_sizes = malloc(pair_num * sizeof(int));
    pairs[0] = malloc(2 * sizeof(int));
    pairs[0][0] = 1;
    pairs[0][1] = 0;
    //pairs[1] = malloc(2 * sizeof(int));
    //pairs[1][0] = 2;
    //pairs[1][1] = 1;
    //pairs[2] = malloc(2 * sizeof(int));
    //pairs[2][0] = 3;
    //pairs[2][1] = 2;
    //pairs[3] = malloc(2 * sizeof(int));
    //pairs[3][0] = 4;
    //pairs[3][1] = 0;
    //pairs[4] = malloc(2 * sizeof(int));
    //pairs[4][0] = 0;
    //pairs[4][1] = 5;

    int count = 0;
    int *ids = findOrder(course_num, pairs, pair_num, col_sizes, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", ids[i]);
    }
    printf("\n");
    return 0;
}
