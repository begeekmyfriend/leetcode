#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void line_fill(char *line, int len, char** words, int *word_lens, int max_size,
                      int even_spaces, int remain_spaces, int start, int end)
{
    int i, j;
    char *p = line;
    for (i = start; i < end; i++) {
        memcpy(p, words[i], word_lens[i]);
        p += word_lens[i];
        if (i < end - 1) {
            for (j = 0; j < even_spaces; j++) {
                *p++ = ' ';
            }
            if (remain_spaces > 0) {
                *p++ = ' ';
                remain_spaces--;
            }
        }
    }
    while (p - line < max_size) {
        *p++ = ' ';
    }
    *p++ = '\0';
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
static char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize)
{
    int i, j, k, cap = 100, count = 0;
    char **lines = malloc(cap * sizeof(char *));
    char *buf = malloc(cap * (maxWidth + 1));
    for (i = 0; i < cap; i++) {
        lines[i] = buf + i * (maxWidth + 1);
    }

    int *word_lens = malloc(wordsSize * sizeof(int));
    for (i = 0; i < wordsSize; i++) {
         word_lens[i] = strlen(words[i]);
    }

    int wc = 0;
    int len = 0;
    int start = 0;
    int chars = 0;
    for (i = 0, j = 0; i < wordsSize; i++) {
        if (len + word_lens[i] > maxWidth) {
            //line_fill(lines[count], len, words, word_lens, maxWidth, chars, wc, start, i);
            int even_spaces = wc == 1 ? 0 : (maxWidth - chars) / (wc - 1);
            int remain_spaces = wc == 1 ? 0 : (maxWidth - chars) % (wc - 1);
            line_fill(lines[count], len, words, word_lens, maxWidth, even_spaces, remain_spaces, start, i);
            count++;
            wc = 1;
            len = word_lens[i] + 1;
            chars = word_lens[i];
            start = i;
        } else if (len + word_lens[i] == maxWidth) {
            chars += word_lens[i];
            int even_spaces = wc == 0 ? 0 : (maxWidth - chars) / wc;
            int remain_spaces = wc == 0 ? 0 : (maxWidth - chars) % wc;            
            line_fill(lines[count], len, words, word_lens, maxWidth, even_spaces, remain_spaces, start, i + 1);
            count++;
            wc = 0;
            len = 0;
            chars = 0;
            start = i + 1;
        } else {
            chars += word_lens[i];
            len += word_lens[i] + 1; /* at least one space */
            wc++;
        }
    }

    if (wc > 0) {
        char *p = lines[count];
        for (i = start; i < start + wc; i++) {
            memcpy(p, words[i], word_lens[i]);
            p += word_lens[i];
            if (i < start + wc - 1) {
                *p++ = ' ';
            }
        }
        while (p - lines[count] < maxWidth) {
            *p++ = ' ';
        }
        *p++ = '\0';
        count++;
    }

    *returnSize = count;
    return lines;
}

int main(int argc, char **argv)
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: ./test maxsize words...\n");
        exit(-1);
    }

    int i, count;
    char** lines = fullJustify(argv + 2, argc - 2, atoi(argv[1]), &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
