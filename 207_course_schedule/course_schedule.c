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

static bool dfs(struct graph_node *courses, int id)
{
    int i;
    if (courses[id].touched) {
        return true;
    } else if (courses[id].taken) {
        return false;
    } else {
        courses[id].taken = true;
        for (i = 0; i < courses[id].req_num; i++) {
            if (!dfs(courses, courses[id].reqs[i])) {
                return false;
            }
        }
        /* If paths overlapped, mark in backtracing for no need to traverse next time */
        courses[id].touched = true;
        courses[id].taken = false;
        return true;
    }
}

static bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
    int i;
    struct graph_node *courses = malloc(numCourses * sizeof(*courses));

    memset(courses, 0, numCourses * sizeof(*courses));
    for (i = 0; i < prerequisitesSize; i++) {
        int id = prerequisites[i][0];
        int req = prerequisites[i][1];
        courses[id].reqs[courses[id].req_num++] = req;
    }

    for (i = 0; i < numCourses; i++) {
        if (!dfs(courses, i)) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int i, course_num = 6, pair_num = 6;
    int **pairs = malloc(pair_num * sizeof(int *));
    int *col_sizes = malloc(pair_num * sizeof(int));
    pairs[0] = malloc(2 * sizeof(int));
    pairs[0][0] = 1;
    pairs[0][1] = 0;
    col_sizes[0] = 2;
    pairs[1] = malloc(2 * sizeof(int));
    pairs[1][0] = 2;
    pairs[1][1] = 1;
    col_sizes[1] = 2;
    pairs[2] = malloc(2 * sizeof(int));
    pairs[2][0] = 3;
    pairs[2][1] = 2;
    col_sizes[2] = 2;
    pairs[3] = malloc(2 * sizeof(int));
    pairs[3][0] = 1;
    pairs[3][1] = 3;
    col_sizes[3] = 2;
    pairs[4] = malloc(2 * sizeof(int));
    pairs[4][0] = 4;
    pairs[4][1] = 0;
    col_sizes[4] = 2;
    pairs[5] = malloc(2 * sizeof(int));
    pairs[5][0] = 0;
    pairs[5][1] = 5;
    col_sizes[5] = 2;
    printf("%s\n", canFinish(course_num, pairs, pair_num, col_sizes) ? "true" : "false");
    return 0;
}
