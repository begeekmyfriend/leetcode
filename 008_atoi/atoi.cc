#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        long n = 0;
        int i, sign = 0;

        for (i = 0; i < str.length(); i++) {
            if (str[i] != ' ' && str[i] != '\t') {
                break;
            }
        }

        if (str[i] == '-') {
            if (isdigit(str[++i])) {
                sign = 1;
            } else {
                return 0;
            }
        }

        if (str[i] == '+') {
            if (isdigit(str[++i])) {
                sign = 0;
            } else {
                return 0;
            }
        }

        for (; i < str.length(); i++) {
            if (isdigit(str[i])) {
                int d = str[i] - '0';
                if (sign) {
                    if (-n < (INT_MIN + d) / 10) {
                        n = INT_MIN;
                        break;
                    }
                } else {
                    if (n > (INT_MAX - d) / 10) {
                        n = INT_MAX;
                        break;
                    }
                }
                n = n * 10 + d;
            } else {
                break;
            }
        }
    
        return sign ? -n : n; 
    }
};
