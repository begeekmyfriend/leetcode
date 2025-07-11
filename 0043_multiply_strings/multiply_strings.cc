#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        vector<int> v(num1.length() + num2.length());
        for (int i = num2.length() - 1; i >= 0; i--) {
            for (int j = num1.length() - 1; j >= 0; j--) {
                int a = num2[j] - '0';
                int b = num1[i] - '0';
                v[i + j + 1] = a * b;
            }
        }

        int i, carry = 0;
        string res(v.size(), '0');
        for (i = v.size() - 1; i >= 0; i--) {
            carry += v[i];
            res[i] += carry % 10;
            carry /= 10;
        }

        for (i = 0; i < res.length() - 1; i++) {
            if (res[i] != '0') {
                break;
            }
        }

        return res.substr(i);
    }
};
