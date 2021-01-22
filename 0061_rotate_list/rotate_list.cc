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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) {
            return head;
        }

        int len = 0;
        ListNode dummy;
        dummy.next = head;
        ListNode *tail = &dummy;
        while (tail->next != nullptr) {
            len++;
            tail = tail->next;
        }

        ListNode *prev = &dummy;
        ListNode *p = head;
        k = k % len;
        for (int i = 0; i < len - k; i++) {
            prev = p;
            p = p->next;
        }

        if (p != nullptr) {
            /* deletion */
            prev->next = tail->next;
            /* insertion */
            tail->next = head;
            head = p;
        }
        return head;
    }
};
