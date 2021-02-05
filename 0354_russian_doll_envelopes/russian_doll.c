#include <stdio.h>
#include <stdlib.h>


static int compare(const void *a, const void *b)
{
    int wa = ((const int *)a)[0];
    int wb = ((const int *)b)[0];
    int ha = ((const int *)a)[1];
    int hb = ((const int *)b)[1];
    return wa == wb ? hb - ha : wa - wb;
}

static int binary_search(int *nums, int lo, int hi, int target)
{
    while (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < target) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize)
{
    if (envelopesSize == 0) {
        return 0;
    }

    int size = envelopesColSize[0];
    int i, *tmp = malloc(envelopesSize * size * sizeof(int));
    for (i = 0; i < envelopesSize; i++) {
        tmp[i * size] = envelopes[i][0];
        tmp[i * size + 1] = envelopes[i][1];
    }
    qsort(tmp, envelopesSize, size * sizeof(int), compare);

    int piles = 0;
    int *heights = malloc(envelopesSize * sizeof(int));
    for (i = 0; i < envelopesSize; i++) {
        int pos = binary_search(heights, -1, piles, tmp[i * size + 1]);
        if (pos == piles) {
            piles++;
        }
        heights[pos] = tmp[i * size + 1];
    }
    return piles;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc % 2 == 0) {
        fprintf(stderr, "Usage: ./test w0 h0 w1 h1...");
        exit(-1);
    }

    int i, size = (argc - 1) / 2;
    int *col_sizes = malloc(size * sizeof(int));
    int **envelopes = malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        col_sizes[i] = 2;
        envelopes[i] = malloc(col_sizes[i] * sizeof(int));
        envelopes[i][0] = atoi(argv[i * 2 + 1]);
        envelopes[i][1] = atoi(argv[i * 2 + 2]);
    }

    printf("%d\n", maxEnvelopes(envelopes, size, col_sizes));
    return 0;
}
