#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res;
        int i = 0;
        int j = numbers.size() - 1;
        while (i < j) {
            int diff = target - numbers[i] - numbers[j];
            if (diff > 0) {
                i++;
            } else if (diff < 0) {
                j--;
            } else {
                res.push_back(i + 1);
                res.push_back(j + 1);
                break;
            }
        }
        return res;
    }
};
