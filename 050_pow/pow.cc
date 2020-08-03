#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if (n == INT_MIN) {
            double t = dfs(x, -(n / 2));
            return 1 / t * 1 / t;
        } else {
            return n < 0 ? 1 / dfs(x, -n) : dfs(x, n);
        }
    }

private:
    double dfs(double x, int n) {
        if (n == 0) {
            return 1;
        } else if (n == 1) {
            return x;
        } else {
            double t = dfs(x, n / 2);
            return (n % 2) ? (x * t * t) : (t * t);
        }
    }
};
