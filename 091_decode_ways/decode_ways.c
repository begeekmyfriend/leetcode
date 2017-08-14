#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//static void recursive(char *s, char *stack, int len, char **results, int *count)
//{
//    if (*s == '\0') {
//        printf("%s\n", stack);
//        results[*count] = malloc(len + 1);
//        strcpy(results[*count], stack);
//        (*count)++;
//    } else {
//        //while (*s != '\0') {
//            stack[len++] = *s - '0' - 1 + 'A';
//            recursive(s + 1, stack, len, results, count);
//            stack[--len] = '\0';
//            if (*(s + 1) != '\0') {
//                int value = (*s - '0') * 10 + (*(s + 1) - '0');
//                char c = (value - 1) + 'A';
//                if (c >= 'A' && c <= 'Z') {
//                    stack[len++] = c;
//                    recursive(s + 2, stack, len, results, count);
//                    stack[--len] = '\0';
//                    //s++;
//                }
//            }
//            //s++;
//        //}
//    }
//}

static void recursive(char *s, int *count)
{
    int value;
    char c;
    if (*s == '\0') {
        (*count)++;
    } else {
        value = *s - '0';
        c = (value - 1) + 'A';
        if (c >= 'A' && c <= 'Z') {
            recursive(s + 1, count);
        }
        if (*(s + 1) != '\0' && *s != '0') {
            value = (*s - '0') * 10 + (*(s + 1) - '0');
            c = (value - 1) + 'A';
            if (c >= 'A' && c <= 'Z') {
                recursive(s + 2, count);
            }
        }
    }
}

static int numDecodings(char* s) {
    int count = 0;
    if (*s != '\0' && *s != '0') {
        recursive(s, &count);
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }
    printf("%d\n", numDecodings(argv[1]));
    return 0;
}
