#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        int thousand_bit = num / 1000;
        int hundred_bit = (num % 1000) / 100;
        int ten_bit = (num % 100) / 10;
        int one_bit = num % 10;

        if (thousand_bit > 0) {
            if (thousand_bit < 4) {
                for (int i = 0; i < thousand_bit; i++) {
                    roman_numeral.push_back('M');
                }
            }
        }
    
        num2char(hundred_bit, 2);
        num2char(ten_bit, 1);
        num2char(one_bit, 0);
    
        return roman_numeral;
    }

private:
    string roman_numeral;
    void num2char(int bit, int n) {   
        char low, mid, high;

        switch (n) {
        case 2: 
            low = 'C';
            mid = 'D';
            high = 'M';
        break;
        case 1: 
            low = 'X';
            mid = 'L';
            high = 'C';
        break;
        case 0: 
            low = 'I';
            mid = 'V';
            high = 'X';
        break;
        }

        if (bit > 0) {
            switch (bit) {
            case 1:
            case 2:
            case 3: 
                for (int i = 0; i < bit; i++) {
                    roman_numeral.push_back(low);
                }
                break;
            case 4:
                roman_numeral.push_back(low);
                roman_numeral.push_back(mid);
                break;
            case 5:
                roman_numeral.push_back(mid);
                break;
            case 6:
            case 7:
            case 8:
                roman_numeral.push_back(mid); 
                for (int i = 5; i < bit; i++) {
                    roman_numeral.push_back(low);
                }
                break;
            case 9:
                roman_numeral.push_back(low);
                roman_numeral.push_back(high);
                break;
            }
        }
    }
};
