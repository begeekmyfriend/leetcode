#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
        int right = 0;
        int farthest = 0;
        // 1. Exhaust all the right boundries in the location range of [i...right]
        // 2. When the search ends up with i==right, update the right boundry as
        //    the fartest position.
        // 3. When the search ends up with i==right, it records as one jump step */
        for (int i = 0; i < nums.size() - 1; i++) {
            fartest = max(i + nums[i], fartest);
            for (i == right) {
                right = fartest;
                steps++;
            }
        }

        return steps;
    }
};
