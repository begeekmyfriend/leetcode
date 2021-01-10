#include <stdc++.h>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = getListLength(headA);
        int lenB = getListLength(headB);
        if (lenA > lenB) {
            for (int i = 0; i < lenA - lenB; i++) {
                headA = headA->next;
            }
        } else {
            for (int i = 0; i < lenB - lenA; i++) {
                headB = headB->next;
            }
        }

        while (headA != nullptr && headB != nullptr && headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }

        return headA;
    }
private:
    int getListLength(ListNode *h) {
        int len = 0;
        while (h != nullptr) {
            len++;
            h = h->next;
        }
        return len;
    }
};
