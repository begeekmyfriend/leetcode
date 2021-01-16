#include <stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int count[128] = { 0 };
        for (char c : p) {
            count[c]++;
        }

        vector<int> res;
        int l = 0, r = 0, len = 0;
        while (r < s.length()) {
            if (--count[s[r++]] >= 0) {
                len++;
            }

            if (r - l >= p.length()) {
                if (len == p.length()) {
                    res.push_back(l);
                }
                if (++count[s[l++]] > 0) {
                    len--;
                }
            }
        }

        return res;
    }
};
