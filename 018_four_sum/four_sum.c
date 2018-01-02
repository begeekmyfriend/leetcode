#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void k_sum(int *nums, int low, int high, int target, int total,
                  int k, int *stack, int len, int **results, int *count)
{
    int i;
    if (k == 2) {
        while (low < high) {
            int diff = target - nums[low];
            if (diff > nums[high]) {
                while (++low < high && nums[low] == nums[low - 1]) {}
            } else if (diff < nums[high]) {
                while (--high > low && nums[high] == nums[high + 1]) {}
            } else {
                stack[len++] = nums[low];
                stack[len++] = nums[high];
                results[*count] = malloc(total * sizeof(int));
                memcpy(results[*count], stack, total * sizeof(int));
                (*count)++;
                len -= 2;
                while (++low < high && nums[low] == nums[low - 1]) {}
                while (--high > low && nums[high] == nums[high + 1]) {}
            }
        }
    } else {
        /* k > 2 */
        for (i = low; i <= high - k + 1; i++) {
            if (i > low && nums[i] == nums[i - 1]) continue;
            stack[len++] = nums[i];
            k_sum(nums, i + 1, high, target - nums[i], 4, k - 1, stack, len,  results, count);
            len--;
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** fourSum(int* nums, int numsSize, int target, int* returnSize)
{
    if (numsSize < 4) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(*nums), compare);

    *returnSize = 0;
    int i, j, capacity = 50000;
    int **results = malloc(capacity * sizeof(int *));
    int *stack = malloc(4 * sizeof(int));
    k_sum(nums, 0, numsSize - 1, target, 4, 4, stack, 0, results, returnSize);
    return results;
}

int main(void)
{
    int i, count;
    //int nums[] = { 1, 0, -1, 0, -2, 2 };
    //int nums[] = { -3, -2, -1, 0, 0, 1, 2, 3 };
    int nums[] = { 0, 1, 5, 0, 1, 5, 5, -4 };
    int **quadruplets = fourSum(nums, sizeof(nums) / sizeof(*nums), 11, &count);
    for (i = 0; i < count; i++) {
        printf("%d %d %d %d\n", quadruplets[i][0], quadruplets[i][1], quadruplets[i][2], quadruplets[i][3]);
    }

    return 0;
}
