#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode *sortedListToBST(ListNode* head) {
        if (head == nullptr) {
            return NULL;
        } else if (head->next == nullptr) {
            return new TreeNode(head->val);
        } else {
            ListNode *fast = head;
            ListNode *slow = head;
            ListNode *last = slow;
            while (fast != nullptr && fast->next != nullptr) {
                last = slow;
                slow = slow->next;
                fast = fast->next->next;
            }
            last->next = nullptr;
            TreeNode *node = new TreeNode(slow->val);
            node->left = sortedListToBST(head);
            node->right = sortedListToBST(slow->next);
            return node;
        }
    }
};
