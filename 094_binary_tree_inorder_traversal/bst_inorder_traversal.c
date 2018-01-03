#include <stdio.h>
#include <stdlib.h>

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

static void traverse(struct TreeNode *node, int *result, int *count)
{
    if (node->left != NULL) {
        traverse(node->left, result, count);
    }
    
    result[*count] = node->val;
    (*count)++;
    
    if (node->right != NULL) {
        traverse(node->right, result, count);
    }    
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int count = 0;
    int *result = malloc(5000 * sizeof(int));
    traverse(root, result, &count);
    *returnSize = count;
    return result;
}

int main()
{
    int count = 0;
    inorderTraversal(NULL, &count);
    return 0;
}
