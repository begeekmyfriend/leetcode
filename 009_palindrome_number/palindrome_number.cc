#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }
        if (x < 0) {
            return false;
        }
        return x == reverse(x);
    }

private:
    int reverse(int x) {
        int n = 0;
        while (x != 0) {
            // Checking the over/underflow.
            int r = x % 10;
            if (n > INT_MAX / 10 || (n == INT_MAX / 10 && r > 7)) {
                return 0;
            }
            if (n < INT_MIN / 10 || (n == INT_MIN / 10 && r < -8)) {
                return 0;
            }

            n = n * 10 + r;
            x = x / 10;
        }
        return n;
    }
};
