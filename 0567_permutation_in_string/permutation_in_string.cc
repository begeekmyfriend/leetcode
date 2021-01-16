#include <stdc++.h>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int count[128] = { 0 };
        for (char c : s1) {
            count[c]++;
        }

        int l = 0, r = 0, len = 0;
        while (r < s2.length()) {
            if (--count[s2[r++]] >= 0) {
                len++;
            }

            if (r - l >= s1.length()) {
                if (len == s1.length()) {
                    return true;
                }
                if (++count[s2[l++]] > 0) {
                    len--;
                }
            }
        }

        return false;
    }
};
