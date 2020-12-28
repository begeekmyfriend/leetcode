#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        for (; i >= 0 && j >= 0; i--, j--) {
            if (a[i] == '1' && b[j] == '1') {
                if (carry > 0) {
                    res.push_back('1');
                } else {
                    res.push_back('0');
                }
                carry = 1;
            } else if (a[i] == '0' && b[j] == '0') {
                if (carry > 0) {
                    res.push_back('1');
                } else {
                    res.push_back('0');
                }
                carry = 0;
            } else {
                if (carry > 0) {
                    res.push_back('0');
                    carry = 1;
                } else {
                    res.push_back('1');
                    carry = 0;
                }
            }
        }
        
        while (i >= 0) {
            if (a[i--] == '1') {
                if (carry > 0) {
                    res.push_back('0');
                    carry = 1;
                } else {
                    res.push_back('1');
                    carry = 0;
                }
            } else {
                res.push_back(carry + '0');
                carry = 0;
            }
        }

        while (j >= 0) {
            if (b[j--] == '1') {
                if (carry > 0) {
                    res.push_back('0');
                    carry = 1;
                } else {
                    res.push_back('1');
                    carry = 0;
                }
            } else {
                res.push_back(carry + '0');
                carry = 0;
            }
        }
        
        if (carry > 0) {
            res.push_back('1');
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
