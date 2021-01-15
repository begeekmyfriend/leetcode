#include <stdio.h>
#include <stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char * s, char * p, int* returnSize){
    *returnSize = 0;
    int *res = malloc(11000 * sizeof(int));
    int i, pat_len = 0;
    int count[128] = { 0 };
    for (i = 0; p[i] != '\0'; i++) {
        count[p[i]]++;
    }
    pat_len = i;

    int l = 0, r = 0, len = 0;
    while (s[r] != '\0') {
        if (--count[s[r++]] >= 0) {
            len++;
        }
        if (r - l >= pat_len) {
            if (len == pat_len) {
                res[(*returnSize)++] = l;
            }
            if (++count[s[l++]] > 0) {
                len--;
            }
        }
    }

    return res;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }

    char *t = argv[1];
    char *s = argv[2];
    int i, count;
    int *results = findAnagrams(s, t, &count); 
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");

    return 0;
}
