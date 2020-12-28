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
    ListNode* reverseGroup(ListNode* head, int k) {
        int len = 0;
        struct ListNode dummy, *prev = &dummy;
        dummy.next = head;

        for (; head != nullptr; head = head->next) {
            if (++len % k == 0) {
                struct ListNode *p = prev->next;
                while (prev->next != head) {
                    struct ListNode *q = p->next;
                    /* deletion */
                    p->next = q->next;
                    /* insertion */
                    q->next = prev->next;
                    prev->next = q;
                }
                /* iteration */
                prev = p;
                head = p;
            }
        }

        return dummy.next;
    }
};
