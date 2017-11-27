#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Trie {
    struct Trie *subs[27];
    char letters[27];
} Trie;

/** Initialize your data structure here. */
static Trie* trieCreate()
{
    Trie *obj = malloc(sizeof(*obj));
    memset(obj->letters, 0xff, sizeof(obj->letters));
    memset(&obj->subs[0], 0, sizeof(obj->subs));
    return obj;
}

/** Inserts a word into the trie. */
static void trieInsert(Trie* obj, char* word)
{
    while (*word != '\0') {
        int pos = *word - 'a' + 1;
        obj->letters[pos] = *word++;
        if (obj->subs[pos] == NULL) {
            obj->subs[pos] = trieCreate();
        }
        obj = obj->subs[pos];
    }
    obj->letters[0] = '\0';
}

/** Returns if the word is in the trie. */
static bool trieSearch(Trie* obj, char* word)
{
    while (obj != NULL) {
        int pos = *word == '\0' ? 0 : *word - 'a' + 1;
        if (obj->letters[pos] != *word) {
            return false;
        }
        word++;
        obj = obj->subs[pos];
    }
    return true;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
static bool trieStartsWith(Trie* obj, char* prefix)
{
    while (*prefix != '\0') {
        int pos = *prefix - 'a' + 1;
        if (pos < 0 || obj->letters[pos] != *prefix) {
            return false;
        }
        if (*++prefix != '\0') {
            if (obj->subs[pos] == NULL) {
                return false;
            }
            obj = obj->subs[pos];
        }
    }
    return true;
}

static void trieFree(Trie* obj)
{
    int i;
    for (i = 0; i < sizeof(obj->letters); i++) {
        if (obj->subs[i] != NULL) {
            trieFree(obj->subs[i]);
        }
    }
    free(obj);
}

int main(void)
{
    char *word1 = "abc";
    char *word2 = "ab";

    Trie* obj = trieCreate();
    trieInsert(obj, word1);
    printf("%s\n", trieSearch(obj, word1) ? "true" : "false");
    printf("%s\n", trieSearch(obj, word2) ? "true" : "false");
    trieInsert(obj, word2);
    printf("%s\n", trieSearch(obj, word2) ? "true" : "false");
    trieInsert(obj, word2);
    printf("%s\n", trieStartsWith(obj, word2) ? "true" : "false");
    trieFree(obj);
    return 0;
}
