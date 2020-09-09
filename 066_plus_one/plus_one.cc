#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        vector<int> res;
        for (int i = digits.size() - 1; i >= 0; i--) {
            int d = digits[i] + carry;
            res.push_back(d % 10);
            carry = d / 10;
        }
        
        if (carry > 0) {
            res.push_back(carry);
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
