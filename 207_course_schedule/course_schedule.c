#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct graph_node {
    int req_num;
    int reqs[15];
};

static bool dfs(struct graph_node *courses, int id, bool *takens, bool *touched)
{
    int i;
    if (touched[id]) {
        return true;
    } else if (takens[id]) {
        return false;
    } else {
        takens[id] = true;
        for (i = 0; i < courses[id].req_num; i++) {
            if (!dfs(courses, courses[id].reqs[i], takens, touched)) {
                return false;
            }
        }
        /* marked as available and no need to traverse next time */
        touched[id] = true;
        takens[id] = false;
        return true;
    }
}

static bool canFinish(int numCourses, int** prerequisites, int prerequisitesRowSize, int prerequisitesColSize)
{
    int i;
    bool *takens = malloc(numCourses);
    bool *touched = malloc(numCourses);
    struct graph_node *courses = malloc(numCourses * sizeof(*courses));

    memset(courses, 0, numCourses * sizeof(*courses));
    memset(takens, false, numCourses * sizeof(bool));
    memset(touched, false, numCourses * sizeof(bool));

    for (i = 0; i < prerequisitesRowSize; i++) {
        int id = prerequisites[i][0];
        int req = prerequisites[i][1];
        courses[id].reqs[courses[id].req_num++] = req;
    }

    for (i = 0; i < numCourses; i++) {
        if (!dfs(courses, i, takens, touched)) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int i, course_num = 6, pair_num = 6;
    int **pairs = malloc(pair_num * sizeof(int *));
    pairs[0] = malloc(2 * sizeof(int));
    pairs[0][0] = 1;
    pairs[0][1] = 0;
    pairs[1] = malloc(2 * sizeof(int));
    pairs[1][0] = 2;
    pairs[1][1] = 1;
    pairs[2] = malloc(2 * sizeof(int));
    pairs[2][0] = 3;
    pairs[2][1] = 2;
    pairs[3] = malloc(2 * sizeof(int));
    pairs[3][0] = 1;
    pairs[3][1] = 3;
    pairs[4] = malloc(2 * sizeof(int));
    pairs[4][0] = 4;
    pairs[4][1] = 0;
    pairs[5] = malloc(2 * sizeof(int));
    pairs[5][0] = 0;
    pairs[5][1] = 5;
    printf("%s\n", canFinish(course_num, pairs, pair_num, 2) ? "true" : "false");
    return 0;
}
