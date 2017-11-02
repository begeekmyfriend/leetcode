#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool valid(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isPalindrome(char* s)
{
    int len = strlen(s);
    int low = 0;
    int high = len - 1;

    while (low < high) {
        if (!valid(s[low])) {
            low++;
        } else if (!valid(s[high])) {
            high--;
        } else if (s[low] == s[high]) {
            low++;
            high--;
        } else {
            if (isalpha(s[low]) && isalpha(s[high])) {
                int diff = s[low] > s[high] ? s[low] - s[high] : s[high] - s[low];
                if (diff == 'a' - 'A') {
                    low++;
                    high--;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    return low >= high;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%s\n", isPalindrome(argv[1]) ? "true" : "false");
    return 0;
}
