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
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* prev = head;
        ListNode *p = prev->next;
        while (p != nullptr) {
            if (p->val != prev->val) {
                prev->next = p;
                prev = p;
            }
            p = p->next;
        }
        prev->next = p;
        return head;
    }
};
