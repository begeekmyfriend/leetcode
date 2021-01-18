#include <stdc++.h>

using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if (n < 3) {
            return 0;
        }

        vector<bool> marked(n);
        int count = n >> 1;
        for (int i = 3; i * i <= n; i += 2) {
            if (!marked[i]) {
                for (int j = i * i; j < n; j += (i << 1)) {
                    if (!marked[j]) {
                        marked[j] = true;
                        --count;
                    }
                }
            }
        }
        return count;
    }
};
