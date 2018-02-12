#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static int manacher(char *s, char output[])
{
    int i, j;
    char s2[3000] = { '\0' };

    s2[0] = '$';
    for (i = 0; s[i] != '\0'; i++) {
        s2[(i<<1)+1] = '#';
        s2[(i<<1)+2] = s[i];
    }
    s2[(i<<1)+1] = '#';
    int len = (i<<1)+2;
    s2[len] = '\0';
    
    int p[3000] = { 0 }; // 以s2中某一点为中心的回文半径
    int id = 0; // 回文的中心点
    int limit = 0; // 最长回文的右边界点
    int maxLen = 0; // 最大回文长度
    int maxId = 0; // 最长回文的中心点
    for (i = 1; i < len; i++) {
        if (i < limit) {
            p[i] = min(p[2*id-i], limit-i);
        } else {
            p[i] = 1;
        }
        
        while (s2[i+p[i]] == s2[i-p[i]]) {
            p[i]++;
        }
        
        if (i+p[i] > limit) {
            limit = i+p[i];
            id = i;
        }
        if (maxLen < p[i]-1) {
            maxLen = p[i]-1;
            maxId = i;
        }
    }
    
    for (j = 0, i = maxId - maxLen; i <= maxId+maxLen; i++) {
        if (s2[i] != '#') {
            output[j++] = s2[i];
        }
    }
    return maxLen;
}

static char *longestPalindrom(char *s)
{
    int i;
    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);
    if (len <= 1) {
        return s;
    }

    char *palindrome = malloc(2000);
    memset(palindrome, 0, sizeof(palindrome));

    int size = manacher(s, palindrome);
    palindrome[size] = '\0';
    return palindrome;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%s\n", longestPalindrom(argv[1]));
    return 0;
}
