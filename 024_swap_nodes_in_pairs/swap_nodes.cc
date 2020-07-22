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
    ListNode* swapPairs(ListNode* head) {
        struct ListNode dummy, *prev = &dummy, *p = head;
        dummy.next = head;
        while (p != nullptr && p->next != nullptr) {
            struct ListNode *q = p->next;
            /* deletion */
            p->next = q->next;
            /* insertion */
            q->next = prev->next;
            prev->next = q;
            /* iteration */
            prev = p;
            p = p->next;
        }
        return dummy.next;
    }
};
