#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        bool dp[1005][1005];    
        int n = s.size();
        int strlen = 0, start;
        for(int i=n-1; i>=0; i--){
            for(int j=i; j<n; j++){
                dp[i][j] = false;
                if(s[i] == s[j] && (j-i<3 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    if(strlen < j-i+1){
                        strlen = j-i+1;
                        start = i;
                    }
                }
            }
        } 
        return s.substr(start, strlen);
    }
};
