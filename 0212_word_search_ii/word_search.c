#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct trie {
    struct trie *subs[27];
    char letters[27];
    int num;
};

static struct trie* trie_create()
{
    struct trie *obj = malloc(sizeof(*obj));
    memset(obj->letters, 0xff, sizeof(obj->letters));
    memset(&obj->subs[0], 0, sizeof(obj->subs));
    obj->num = 0;
    return obj;
}

static void trie_insert(struct trie* obj, char* word)
{
    while (*word != '\0') {
        int pos = *word - 'a' + 1;
        obj->letters[pos] = *word++;
        obj->num++;
        if (obj->subs[pos] == NULL) {
            obj->subs[pos] = trie_create();
        }
        obj = obj->subs[pos];
    }
    obj->letters[0] = '\0';
}

static void trie_remove(struct trie* obj, char* word)
{
    while (obj != NULL && *word != '\0') {
        int pos = *word++ - 'a' + 1;
        if (--obj->num == 0) {
            obj->letters[pos] = 0xff;
        }
        obj = obj->subs[pos];
    }
    if (obj != NULL) {
        obj->letters[0] = 0xff;
    }
}

static void dfs(char **board, int row_size, int col_size, int row, int col, struct trie *node,
                char *word, int len, bool *used, char **results, int *count, struct trie *root, int *wordsSize)
{
    char c = board[row][col];
    int index = c - 'a' + 1;

    if (node == NULL || node->letters[index] == -1) {
        return;
    }

    printf("%d %d\n", row, col);
    word[len] = c;

    struct trie *sub = node->subs[index];
    if (sub != NULL && sub->letters[0] == '\0') {
        word[len + 1] = '\0';
        results[*count] = malloc(len + 2);
        strcpy(results[*count], word);
        (*count)++;
        trie_remove(root, word);
        (*wordsSize)--;
        printf("%s\n", word);
    }

    used[row * col_size + col] = true;

    if (row > 0 && !used[(row - 1) * col_size + col]) {
        dfs(board, row_size, col_size, row - 1, col, node->subs[index], word, len + 1, used, results, count, root, wordsSize);
    }

    if (row < row_size - 1 && !used[(row + 1) * col_size + col]) {
        dfs(board, row_size, col_size, row + 1, col, node->subs[index], word, len + 1, used, results, count, root, wordsSize);
    }

    if (col > 0 && !used[row * col_size + col - 1]) {
        dfs(board, row_size, col_size, row, col - 1, node->subs[index], word, len + 1, used, results, count, root, wordsSize);
    }

    if (col < col_size - 1 && !used[row * col_size + col + 1]) {
        dfs(board, row_size, col_size, row, col + 1, node->subs[index], word, len + 1, used, results, count, root, wordsSize);
    }

    used[row * col_size + col] = false;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
static char **findWords(char** board, int boardRowSize, int boardColSize, char** words, int wordsSize, int* returnSize)
{
    int i, j, cap = 5000;
    struct trie *root = trie_create();
    for (i = 0; i < wordsSize; i++) {
        trie_insert(root, words[i]);
    }

    *returnSize = 0;
    char *word = malloc(boardRowSize * boardColSize + 1);
    memset(word, 0, boardRowSize * boardColSize + 1);
    char **results = malloc(cap * sizeof(char *));
    bool *used = malloc(boardRowSize * boardColSize);
    memset(used, false, boardRowSize * boardColSize);
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            if (wordsSize == 0) {
                return results;
            }
            dfs(board, boardRowSize, boardColSize, i, j, root, word, 0, used, results, returnSize, root, &wordsSize);
        }
    }
    return results;
}

int main(void)
{
    int i;
#if 0
    int row = 4;
    int col = 4;
    char **board = malloc(row * sizeof(char *));
    board[0] = malloc(col);
    board[0][0] = 'o';
    board[0][1] = 'a';
    board[0][2] = 'a';
    board[0][3] = 'n';
    board[1] = malloc(col);
    board[1][0] = 'e';
    board[1][1] = 't';
    board[1][2] = 'a';
    board[1][3] = 'e';
    board[2] = malloc(col);
    board[2][0] = 'i';
    board[2][1] = 'h';
    board[2][2] = 'k';
    board[2][3] = 'r';
    board[3] = malloc(col);
    board[3][0] = 'i';
    board[3][1] = 'f';
    board[3][2] = 'l';
    board[3][3] = 'v';

    int size = 4;
    char **words = malloc(size * sizeof(char *));
    words[0] = malloc(5);
    strcpy(words[0], "oath");
    words[1] = malloc(5);
    strcpy(words[1], "pea");
    words[2] = malloc(5);
    strcpy(words[2], "eat");
    words[3] = malloc(5);
    strcpy(words[3], "rain");
#else
    int row = 2;
    int col = 2;
    char **board = malloc(row * sizeof(char *));
    board[0] = malloc(col);
    board[0][0] = 'a';
    board[0][1] = 'b';
    board[1] = malloc(col);
    board[1][0] = 'a';
    board[1][1] = 'a';

    int size = 7;
    char **words = malloc(size * sizeof(char *));
    words[0] = malloc(5);
    words[1] = malloc(5);
    words[2] = malloc(5);
    words[3] = malloc(5);
    words[4] = malloc(5);
    words[5] = malloc(5);
    words[6] = malloc(5);
    strcpy(words[0], "aba");
    strcpy(words[1], "baa");
    strcpy(words[2], "bab");
    strcpy(words[3], "aaab");
    strcpy(words[4], "aaa");
    strcpy(words[5], "aaaa");
    strcpy(words[6], "aaba");
#endif

    int count = 0;
    char **lists = findWords(board, row, col, words, size, &count);
    for (i = 0; i < count; i++) {
        printf("%s\n", lists[i]);
    }
    return 0;
}
