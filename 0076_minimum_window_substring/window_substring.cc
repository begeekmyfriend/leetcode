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
        int hit_num = 0;
        int start = 0, min_len = INT_MAX;
        while (r < s.length()) {
            // counting each letter in the string. The zero and positive
            // countings indicate ones in pattern. And the negative ones
            // indicate those out of the pattern.
            if (--count[s[r++]] >= 0) {
                hit_num++;
            }

            while (hit_num == t.length()) {
                if (r - l < min_len) {
                    start = l;
                    min_len = r - l;
                }
                // The countings of the letter larger than zero shall be
                // the ones in the pattern.
                if (++count[s[l++]] > 0) {
                    hit_num--;
                }
            }
        }

        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};
