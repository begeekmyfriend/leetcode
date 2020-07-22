#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int curr = roman_to_integer(s[0]);
        int result = curr;

        for (int i = 1; i < s.length(); i++) {
            int prev = curr;
            curr = roman_to_integer(s[i]);
            /* left < right : IV(4), XL(40), IX(9) ... */
            if (prev < curr) {
                result -= prev - (curr - prev);
            } else {
                result += curr;
            }
        }

        return result;
    }

private:
    int roman_to_integer(char c) {
        switch(c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }
};
