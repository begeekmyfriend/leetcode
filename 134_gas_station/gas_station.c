#include <stdio.h>
#include <stdlib.h>

static int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize)
{
    int i, j, store = 0, start = -1;
    for (i = 0; i < gasSize; i++) {
        if (start < 0) {
            start = i;
        }
        store += gas[i] - cost[i];
        if (store < 0) {
            store = 0;
            start = -1;
        }
    }
    if (start > 0) {
        for (i = 0; i < start; i++) {
            store += gas[i] - cost[i];
            if (store < 0) {
                return -1;
            }
        }
    }
    return start;
}

int main(void)
{
    int gas[] = { 4 };
    int cost[] = { 5 };
    int count = sizeof(gas) / sizeof(*gas);
    printf("%d\n", canCompleteCircuit(gas, count, cost, count));
    return 0;
}
