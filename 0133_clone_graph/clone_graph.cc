#include <bits/stdc++.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return node;
        }
#if 1 // DFS
        if (cloned.find(node) != cloned.end()) {
            return cloned[node];
        }

        cloned[node] = new Node(node->val);

        for (auto& neighbor : node->neighbors) {
            cloned[node]->neighbors.emplace_back(cloneGraph(neighbor));
        }
#else // BFS
        queue<Node *> q;
        q.push(node);
        cloned[node] = new Node(node->val);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto n = q.front();
                q.pop();

                for (auto& neighbor : n->neighbors) {
                    if (cloned.find(neighbor) == cloned.end()) {
                        cloned[neighbor] = new Node(neighbor->val);
                        q.push(neighbor);
                    }
                    cloned[n]->neighbors.emplace_back(cloned[neighbor]);
                }
            }
        }
#endif
        return cloned[node];
    }
private:
    unordered_map<Node *, Node *> cloned;   
};
