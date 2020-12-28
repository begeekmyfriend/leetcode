#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static char** letterCombinations(char* digits, int* returnSize)
{
    int i, j, k;
    int empty = 1;
    int count = 1;
    int digit_len = strlen(digits);
    char *letter_matrix[10] = {"", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", };
    int letter_length[10] = {0, 1, 3, 3, 3, 3, 3, 4, 3, 4, };

    for (i = 0; i < digit_len; i++) {
        int index = digits[i] - '0';
        if (letter_length[index] > 0) {
            empty = 0;
            count *= letter_length[index];
        }
    }

    if (empty) {
	*returnSize = 0;
        return NULL;
    }

    *returnSize = count;

    char **letters = malloc(sizeof(char *) * count);
    for (i = 0; i < count; i++) {
        letters[i] = malloc(digit_len + 1);
        memset(letters[i], 0, digit_len + 1);
    }

    int den = 1;
    for (i = digit_len - 1; i > 0; i--) {
        int index = digits[i] - '0';
        if (letter_length[index] > 0) {
            den *= letter_length[index];
        }
    }

    int col = 0;
    for (i = 0; i < digit_len; i++) {
        int index = digits[i] - '0';
        if (letter_length[index] > 0) {
            if (i > 0) {
		int index2 = digits[i] - '0';
                if (letter_length[index2] > 0) {
		    den /= letter_length[index2];
                }
            }
            for (j = 0; j < count; j++) {
                k = j / den % letter_length[index];
                letters[j][col] = letter_matrix[index][k];
            }
            col++;
        }
    }

    return letters;
}

int main(int argc, char **argv) {
    int i, size = 0;
    char ** letters = letterCombinations(argv[1], &size);
    for (i = 0; i < size; i++) {
        printf("%s\n", letters[i]);
        free(letters[i]);
    }
    free(letters);
    return 0;
}
