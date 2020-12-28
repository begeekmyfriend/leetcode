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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        struct ListNode *prev, dummy;

        prev = &dummy;
        dummy.next = l1;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                prev = l1;
                l1 = l1->next;
            } else {
                struct ListNode *tmp = l2;
                l2 = l2->next;
                tmp->next = l1;
                prev->next = tmp;
                prev = tmp;
            }
        }

        if (l2 != nullptr) {
            prev->next = l2;
        }

        return dummy.next;
    }
};
