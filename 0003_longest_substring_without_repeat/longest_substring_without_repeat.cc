#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> count(256);
        int len = 0;
        int i, j;

        for (i = 0, j = 0; i < s.length(); i++) {
            count[s[i]]++;
            while (count[s[i]] > 1) {
                len = i - j > len ? i - j : len;
                count[s[j++]] -= 1;
            }
        }

        return i - j > len ? i - j : len;
    }
};
