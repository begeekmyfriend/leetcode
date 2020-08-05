#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;         
        for (const auto i : nums) {
            strs.push_back(to_string(i));
        }

        auto cmp = [](string s1, string s2) { return s1 + s2 > s2 + s1; };
        sort(strs.begin(), strs.end(), cmp);

        if (strs[0] == "0") {
            return "0";
        }

        string res;
        for (const auto& s : strs) {
            res += s;
        }
        return res;
    }
};
