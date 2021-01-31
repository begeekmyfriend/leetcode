#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        unsigned int lo = 1, hi = x;
        unsigned int mid = (lo + hi) / 2;
        for (; ;) {
            if (mid > x / mid) {
                hi = mid;
            } else {
                if (mid + 1 > x / (mid + 1)) {
                    break;
                } else {
                    lo = mid;
                }
            }
            mid = (lo + hi) / 2;
        }

        return mid;
    }
};
