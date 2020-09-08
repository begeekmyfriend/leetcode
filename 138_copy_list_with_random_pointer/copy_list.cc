#include <bits/stdc++.h>

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node *p, *q;
        // Insert interleavingly
        for (p = head; p != nullptr; p = q->next) {
            q = Node(p->val);
            q->next = p->next;
            p->next = q;
        }

        // Clone random pointers
        for (p = head; p != nullptr; p = q->next) {
            q = p->next;
            q->random = p->random != nullptr ? p->random->next : nullptr;
        }

        // Separate q list
        Node dummy;
        Node *prev = &dummy;
        prev->next = head;
        for (p = head; p != nullptr; p = q->next) {
            q = p->next;
            p->next = q->next; // restore p->next
            prev->next = q;
            prev = q;
        }
        /* q->next == nullptr */

        return dummy.next;
    }
};
