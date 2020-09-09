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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](struct ListNode *n1, struct ListNode *n2) {
            return n1->val > n2->val;
        }
        priority_queue<struct ListNode*, vector<struct ListNode*>, decltype(cmp)> queue(cmp);

        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                queue.push(lists[i]);
            }
        }

        struct ListNode dummy, *p = &dummy;;
        while (!queue.empty()) {
            ListNode *node = queue.top();
            queue.pop();
            p->next = node;
            p = node;
            if (node->next != nullptr) {
                queue.push(node->next);
            }
        }

        return dummy.next;
    }
};
