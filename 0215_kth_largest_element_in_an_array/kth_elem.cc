#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> queue;
        for (const auto i : nums) {
            if (queue.size() < k) {
                queue.push(i);
            } else if (i > queue.top()) {
                queue.pop();
                queue.push(i);
            }
        }
        return queue.top();
    }
};
