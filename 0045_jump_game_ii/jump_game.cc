#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
        int right = 0;
        int farthest = 0;
        // 1. Exhaust all the right boundries in the location range of [i...farthest]
        // 2. When i reaches the farthest boundary, update the farthest boundry
        // and the step number.
        // 3. Apply condition i < size - 1 and iterator i++ to avoid overflow.
        for (int i = 0; i < nums.size() - 1; i++) {
            right = max(i + nums[i], right);
            if (i == farthest) {
                farthest = right;
                steps++;
            }
        }

        return steps;
    }
};
