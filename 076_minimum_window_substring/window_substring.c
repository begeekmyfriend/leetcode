#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static char *minWindow(char *s, char *t)
{
    /*
     * Declare two "hash map" for ASCII chars
     *   f[]: represents the char found in s
     *   m[]: stores the chars in t
     */    
    int i, f[256], m[256], pat_len = 0;
    const int NOT_EXISTED   = -1;
    const int NOT_FOUND     =  0;
    memset(m, NOT_EXISTED, sizeof(m));
    memset(f, NOT_EXISTED, sizeof(f));

    /* 
     *  Go through t, and inital the m[] and f[] 
     *  Notes: a same char can be appeared multiple times.
     */
    for (i = 0; t[i] != '\0'; i++) {
        m[t[i]] == NOT_EXISTED ? m[t[i]] = 1 : m[t[i]]++; 
        f[t[i]] = NOT_FOUND;
        pat_len++;
    }

    int start =-1;
    int winSize = INT_MAX;
    int letterFound = 0;
    int begin = 0;
    for (i = 0; s[i] != '\0'; i++) {
        /* if s[i] is existed in t */ 
        if (m[s[i]] != NOT_EXISTED){
            f[s[i]]++;

            /* if one char has been found enough times, then do not do letterFound++ */
            if (f[s[i]] <= m[s[i]]) {
                letterFound++;
            }
            if (letterFound >= pat_len) {
                /* 
                 * Find the beginning of the window
                 * 1) f[s[begin]] == NOT_EXISTED  ===> the char at the `begin` is not in t
                 * 2) f[s[begin]] > m[s[begin]]   ===> a same char appeared more than excepted.
                 */
                while ( f[s[begin]] == NOT_EXISTED || f[s[begin]] > m[s[begin]] ) { 
                    if ( f[s[begin]] > m[s[begin]] ) {
                        f[s[begin]]--;
                    }   
                    begin++;
                }
                /* Calculate the minimized window size */
                if(winSize > i - begin + 1){
                    start = begin;
                    winSize = i - begin + 1;
                }     
            }
        }
    }

    char *result = NULL;
    if (start>=0 && winSize>0) {
        result = malloc(winSize + 1);
        memcpy(result, s + start, winSize);
        result[winSize] = '\0';
    } else {
        result = malloc(1);
        result[0] = '\0';
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }
    printf("Answer: %s\n", minWindow(argv[1], argv[2]));
    return 0;
}
