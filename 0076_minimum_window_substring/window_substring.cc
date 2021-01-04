#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        for (char c : t) {
            count[c]++;
        }

        int l = 0, r = 0;
        int need_to_meet = t.length();
        int start, min_len = INT_MAX;
        while (r < s.length()) {
            if (--count[s[r++]] >= 0) {
                need_to_meet--;
            }

            while (need_to_meet == 0) {
                if (r - l < min_len) {
                    start = l;
                    min_len = r - l;
                }
                if (++count[s[l++]] > 0) {
                    need_to_meet++;
                }
            }
        }

        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};
