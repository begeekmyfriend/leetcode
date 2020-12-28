#include <stdio.h>
#include <stdlib.h>

static int candy(int* ratings, int ratingsSize)
{
    if (ratingsSize == 0) return 0;
    if (ratingsSize == 1) return 1;

    int i, *candies = malloc(ratingsSize * sizeof(int));
    candies[0] = 1;  

    for (i = 1; i < ratingsSize; i++) {  
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;  
        } else {
            /* Set as least so that it will be reset from the opposite side */
            candies[i] = 1;  
        }
    }  

    int sum = candies[ratingsSize - 1];
    for (i = ratingsSize - 2; i >= 0; i--) {  
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {  
            candies[i] = candies[i + 1] + 1;  
        }
        sum += candies[i];
    }  

    return sum;  
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", candy(nums, count));
    return 0;
}
