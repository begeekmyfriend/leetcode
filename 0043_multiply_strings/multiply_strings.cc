#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        string res(num1.length() + num2.length(), '0');
        for (int i = num2.length() - 1; i >= 0; i--) {
            int j, carry = 0;
            for (j = num1.length() - 1; j >= 0; j--) {
                carry += (num1[j] - '0') * (num2[i] - '0') + (res[i + j + 1] - '0');
                res[i + j + 1] = carry % 10 + '0';
                carry /= 10;
            }
            res[i + j + 1] = carry + '0';
        }

        int i;
        for (i = 0; i < res.length() - 1; i++) {
            if (res[i] != '0') {
                break;
            }
        }
        return res.substr(i);
    }
};
