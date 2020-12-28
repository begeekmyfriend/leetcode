#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }

        string new_s;
        for (int row = 0; row < numRows; row++) {
            int delta;
            int interval1 = numRows + (numRows - 2) - row * 2;
            int interval2 = 2 * row;
            bool flag = false;
            for (int i = row; i < s.length(); i += delta) {
                new_s.push_back(s[i]);
                do {
                    delta = !flag ? interval1 : interval2;
                    flag = !flag;
                } while (delta == 0);
            }
        }

        return new_str;
    }
};
