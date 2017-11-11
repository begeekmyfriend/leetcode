#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int min_idx;
    int stack[];
} MinStack;

/** initialize your data structure here. */
static MinStack* minStackCreate(const int maxSize)
{
    MinStack* obj = malloc(sizeof(MinStack) + sizeof(int) * maxSize);
    obj->num = 0;
    obj->min_idx = 0;
    return obj;
}

static void minStackPush(MinStack* const obj, const int x)
{
    if (obj->num > 0 && x < obj->stack[obj->min_idx]) {
        obj->min_idx = obj->num;
    }
    obj->stack[obj->num++] = x;
}

static void minStackPop(MinStack* const obj)
{
    int i;
    if (--obj->num == obj->min_idx) {
        int min_idx = 0;
        for (i = 1; i < obj->num; i++) {
            if (obj->stack[i] < obj->stack[min_idx]) {
                min_idx = i;
            }
        }
        obj->min_idx = min_idx;
    }
}

static int minStackTop(MinStack* const obj)
{
    return obj->stack[obj->num - 1];
}

static int minStackGetMin(MinStack* const obj)
{
    return obj->stack[obj->min_idx];
}

static void minStackFree(MinStack* const obj)
{
    free(obj);    
}

int main(void)
{
    MinStack *obj = minStackCreate(5);
    minStackPush(obj, 2);
    minStackPush(obj, 0);
    minStackPush(obj, 3);
    minStackPush(obj, 0);
    printf("Min:%d\n", minStackGetMin(obj));
    minStackPop(obj);
    //printf("Top:%d\n", minStackTop(obj));
    printf("Min:%d\n", minStackGetMin(obj));
    minStackPop(obj);
    printf("Min:%d\n", minStackGetMin(obj));
    minStackPop(obj);
    printf("Min:%d\n", minStackGetMin(obj));
    minStackFree(obj);
    return 0;
}
