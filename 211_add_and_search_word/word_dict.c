#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct WordDictionary {
    struct WordDictionary *subs[27];
    char letters[27];
} WordDictionary;

/** Initialize your data structure here. */
static WordDictionary* wordDictionaryCreate()
{
    WordDictionary *obj = malloc(sizeof(*obj));
    memset(obj->letters, 0xff, sizeof(obj->letters));
    memset(&obj->subs[0], 0, sizeof(obj->subs));
    return obj;
}

/** Inserts a word into the wordDictionary. */
static void wordDictionaryInsert(WordDictionary* obj, char* word)
{
    while (*word != '\0') {
        int pos = *word - 'a' + 1;
        obj->letters[pos] = *word++;
        if (obj->subs[pos] == NULL) {
            obj->subs[pos] = wordDictionaryCreate();
        }
        obj = obj->subs[pos];
    }
    obj->letters[0] = '\0';
}

/** Returns if the word is in the wordDictionary. */
static bool wordDictionarySearch(WordDictionary* obj, char* word)
{
    int i;
    while (obj != NULL) {
        if (*word == '.') {
            bool found;
            for (i = 1; i < sizeof(obj->letters); i++) {
                if (obj->subs[i] != NULL) {
                    found = wordDictionarySearch(obj->subs[i], word + 1);
                    if (found) {
                        return true;
                    }
                }
            }
            return false;
        } else {
            int pos = *word == '\0' ? 0 : *word - 'a' + 1;
            if (obj->letters[pos] != *word) {
                return false;
            }
            word++;
            obj = obj->subs[pos];
        }
    }
    return true;
}

static void wordDictionaryFree(WordDictionary* obj)
{
    int i;
    for (i = 0; i < sizeof(obj->letters); i++) {
        if (obj->subs[i] != NULL) {
            wordDictionaryFree(obj->subs[i]);
        }
    }
    free(obj);
}

int main(void)
{
    char *word1 = "abc";
    char *word2 = "ab";
    char *word3 = "...";

    WordDictionary* obj = wordDictionaryCreate();
    wordDictionaryInsert(obj, word1);
    printf("%s\n", wordDictionarySearch(obj, word1) ? "true" : "false");
    printf("%s\n", wordDictionarySearch(obj, word2) ? "true" : "false");
    wordDictionaryInsert(obj, word2);
    printf("%s\n", wordDictionarySearch(obj, word2) ? "true" : "false");
    wordDictionaryInsert(obj, word2);
    printf("%s\n", wordDictionarySearch(obj, word3) ? "true" : "false");
    wordDictionaryFree(obj);
    return 0;
}
