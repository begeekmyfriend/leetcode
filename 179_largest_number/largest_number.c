#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char buf[16];
    int index;
};

static int compare(const char *c1, const char *c2)
{
    char p1[32];
    char p2[32];
    p1[0] = '\0';
    p2[1] = '\0';
    strcat(p1, c1);
    strcat(p1, c2);
    strcat(p2, c2);
    strcat(p2, c1);
    return strcmp(p1, p2);
}

static void bubble_sort(struct object *objs, int size)
{
    int i, flag = size;
    while (flag) {
        int len = flag;
        flag = 0;
        for (i = 1; i < len; i++) {
            if (compare(objs[i].buf, objs[i - 1].buf) > 0) {
                struct object tmp = objs[i];
                objs[i] = objs[i - 1];
                objs[i - 1] = tmp;
                flag = i;
            }
        }
    }
}

static char* largestNumber(int* nums, int numsSize)
{
    int i;
    struct object *objs = malloc(numsSize * sizeof(*objs));
    memset(objs, 0, sizeof(*objs));
    for (i = 0; i < numsSize; i++) {
        objs[i].index = i;
        sprintf(objs[i].buf, "%d", nums[i]);
    }

    bubble_sort(objs, numsSize);
    if (objs[0].buf[0] == '0') {
        return "0";
    }

    char *result = malloc(numsSize * 16);
    result[0] = '\0';
    for (i = 0; i < numsSize; i++) {
        strcat(result, objs[i].buf); 
    }

    return result;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%s\n", largestNumber(nums, count));
    return 0;
}
