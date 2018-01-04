#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char buf[16];
};

static int compare(const void *o1, const void *o2)
{
    char p1[32];
    char p2[32];
    p1[0] = '\0';
    p2[0] = '\0';
    strcat(p1, ((struct object *) o1)->buf);
    strcat(p1, ((struct object *) o2)->buf);
    strcat(p2, ((struct object *) o2)->buf);
    strcat(p2, ((struct object *) o1)->buf);
    return strcmp(p1, p2);
}

static char* largestNumber(int* nums, int numsSize)
{
    int i;
    struct object *objs = malloc(numsSize * sizeof(*objs));
    memset(objs, 0, sizeof(*objs));
    for (i = 0; i < numsSize; i++) {
        sprintf(objs[i].buf, "%d", nums[i]);
    }

    qsort(objs, numsSize, sizeof(*objs), compare);
    if (objs[numsSize - 1].buf[0] == '0') {
        return "0";
    }

    char *result = malloc(numsSize * 16);
    result[0] = '\0';
    for (i = numsSize - 1; i >= 0; i--) {
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
