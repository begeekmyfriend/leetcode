#include <stdio.h>
#include <stdlib.h>


int brokenCalc(int X, int Y)
{
    int step = 0;
    while (X < Y) {
        Y = Y & 1 ? Y + 1 : Y / 2;
        step++;
    }
    step += X - Y;    
    return step;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test x y");
        exit(-1);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    printf("%d\n", brokenCalc(x, y));
    return 0;
}
