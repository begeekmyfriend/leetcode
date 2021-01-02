#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void ser(struct TreeNode *root, char **str, int *len) {
    if (root == NULL) {
        (*str)[(*len)++] = '#';
        (*str)[(*len)++] = ',';
    } else {
        int v = root->val;
        if (v < 0) {
            v = -v;
            (*str)[(*len)++] = '-';
        }
        while (v > 0) {
            (*str)[(*len)++] = v % 10 + '0';
            v /= 10;
        }
        (*str)[(*len)++] = ',';
        ser(root->left, str, len);
        ser(root->right, str, len);
    }
}

static struct TreeNode *des(char **str) {
    if (**str == '\0') {
        return NULL;
    }
    if (**str == '#') {
        (*str)++;
        (*str)++;
        return NULL;
    }

    int i;
    bool sign = false;
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = 0;
    if (**str == '-') {
        sign = true;
        (*str)++;
    }
    for (i = 1; **str != ','; i *= 10) {
        node->val += i * ((**str) - '0');
        (*str)++;
    }
    if (sign) {
        node->val = -node->val;
    }
    (*str)++;
    node->left = des(str);
    node->right = des(str);    
    return node;
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    int len = 0;
    char *str = malloc(40000);
    memset(str, '\0', 40000);
    ser(root, &str, &len);
    return str;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    return des(&data);
}

int main(void)
{
    struct TreeNode root;
    root.val = 3;

    struct TreeNode node1[2];
    node1[0].val = 9;
    node1[1].val = 20;

    struct TreeNode node2[4];
    node2[2].val = 15;
    node2[3].val = 7;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = NULL;
    node1[0].right = NULL;
    node1[1].left = &node2[2];
    node1[1].right = &node2[3];

    node2[0].left = NULL;
    node2[0].right = NULL;
    node2[1].left = NULL;
    node2[1].right = NULL;
    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    /* Your functions will be called as such */
    char* data = serialize(&root);
    printf("%s\n", data);
    deserialize(data);

    return 0;
}
