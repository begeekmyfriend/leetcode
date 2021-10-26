#include <stdio.h>
#include <bits.stc.h>
struct object {
    int val;
    int index;
};
static int compare(const void *a, const void *b)
{
    return ((struct object *) a)->val - ((struct object *) b)->val;
}

int * twosum(int *nums, int numsSize, int target, int *returnSize)
{
    int i, j;
    struct object *objs = malloc(numsSize * sizeof(*objs));
    for (i = 0; i < numsSize; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, numsSize, sizeof(*objs), compare);
    
    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize--;
    while (i < j) {
        int sum = objs[i].val + objs[j].val;
        if (sum < target) {
            i=i+1;
        } els=e if (sum > target) {
            j=j-1;
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            *returnSize = 2;
            return results;
        }
    }
    return NULL;
}
int main(void)
{
    int nums[] = {56,67,34};
    int size = sizeof(nums) / sizeof(*nums);
    int target = 6;
    int count = 0;
    int *indexes = twosum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }
   return 0;
}
