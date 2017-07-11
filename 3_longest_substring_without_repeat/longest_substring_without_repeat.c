#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int lengthOfLongestSubstring(char *s) {
    int offset[128];
    int max_len = 0;
    char *p, *q;
    int len = 0;
    memset(offset, 0xff, sizeof(offset));
    for (p = s; *p != '\0'; p++) {
        for (q = p; *q != '\0'; q++) {
            if (offset[*q] == -1) {
                offset[*q] = q - s;
                if (++len > max_len) {
                    max_len = len;
                }
            } else {
	        len = 0;
                p = offset[*q] + s;
                memset(offset, 0xff, sizeof(offset));
                break;
            }
        }
    }
    return max_len;
}

int main(int argc, char **argv)
{
    printf("%d\n", lengthOfLongestSubstring(argv[1]));
    return 0;
}
