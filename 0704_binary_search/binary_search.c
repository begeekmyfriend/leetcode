#include <stdio.h>

int search(int* nums, int numsSize, int target){
    if(target > nums[numsSize-1] || target < nums[0])return -1;
    int begin = -1 ,end = numsSize;
    while(begin < end-1){
        int half = (begin+end)/2;
        if(nums[half]<target)begin = half;
            else end = half;
    }
    if(nums[end]==target) return end ;
    else return -1; 
}

int main(void) {
  int test[6] = {-1,0,3,5,9,12};
  
  //test 1 - number 2;
  printf("possible index = %d\n",search(test,6,2));
  //test 2 - number 9
  printf("possible index = %d\n",search(test,6,9));
  return 0;
}