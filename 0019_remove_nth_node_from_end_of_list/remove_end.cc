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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (n == 0) {
            return nullptr;
        }

        struct ListNode *p, *prev, dummy;
        dummy.next = head;
        p = prev = &dummy;
        while (n-- > 0) {
            p = p->next;
        }

        while (p->next != nullptr) {
            p = p->next;
            prev = prev->next;
        }

        struct ListNode *tmp = prev->next;
        prev->next = tmp->next;
        if (tmp == head) {
            head = tmp->next;
        }

        return head;
    }
};
