#include <stdc++.h>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int count[128] = { 0 };
        for (char c : s1) {
            count[c]++;
        }

        int l = 0, r = 0, hits = 0;
        while (r < s2.length()) {
            if (--count[s2[r++]] >= 0) {
                hits++;
            }

            // When the window length equals to the hit length,
            // the permutation is contained.
            if (r - l >= s1.length()) {
                if (hits == s1.length()) {
                    return true;
                }
                if (++count[s2[l++]] > 0) {
                    hits--;
                }
            }
        }

        return false;
    }
};
