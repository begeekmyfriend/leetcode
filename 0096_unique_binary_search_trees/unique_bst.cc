#include <stdc++.h>

using namespace std;

/*
 * f(n) = f(0)f(n-1) + f(1)f(n-2) + ... + f(n-2)f(1) + f(n-1)f(0)
 */
class Solution {
public:
    int numTrees(int n) {
        vector<int> sum(n + 1);
        sum[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                sum[i] += sum[j] * sum[i - j - 1];
            }
        }
        return sum[n];
    }
}
