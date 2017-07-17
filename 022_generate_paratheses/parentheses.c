#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
char** generateParenthesis(int n, int* returnSize) {
    int left, right, cap = 1, count = 0;
    char *parenthese = malloc(2 * n + 1);
    char **par_lists = malloc(cap * sizeof(char *));

    char *p = parenthese;
    left = right = 0;
    parenthese[2 * n] = '\0';

    /* begin and end condition of loop */
    while (count == 0 || p != parenthese) {
        if (left == n && right == n) {
            /* new parentheses */
            if (count + 1 >= cap) {
                cap *= 2;
                par_lists = realloc(par_lists, cap * sizeof(char *));
            }
            par_lists[count] = malloc(2 * n + 1);
            strcpy(par_lists[count], parenthese);
            count++;

            /* back tracking */
            while (--p != parenthese) {
                if (*p == '(') {
                    /* until ')' is no more than '(' is guaranteed */
                    if (--left > right) {
                        *p++ = ')';
                        right++;
                        break;
                    }
                } else {
                    right--;
                }
            }
        } else {
            /* forward */
            while (left < n) {
                *p++ = '(';
                left++;
            }
            while (right < n) {
                *p++ = ')';
                right++;
            }
        }
    }

    *returnSize = count;
    return par_lists;
}

int main(int argc, char **argv)
{
    int i, count;
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test 3\n");
        exit(-1);
    }
    char ** lists = generateParenthesis(atoi(argv[1]), &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", lists[i]);
    }
    return 0;
}
