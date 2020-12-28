#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> indexes(128, -1);
        int max_len = 0;
        int len = 0;

        for (int i = 0; i < s.length(); i++) {
            if (indexes[s[i]] == -1) {
                len++;
            } else {
                if (i - indexes[s[i]] > len) {
                    /* not included in sliding window, go on increasing */
                    len++;
                } else {
                    /* repetition in sliding window, count from scratch */
                    len = i - indexes[s[i]];
                }
            }
            max_len = max(max_len, len);
            indexes[s[i]] = i;
        }

        return max_len;
    }
};
