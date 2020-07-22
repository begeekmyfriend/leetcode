#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.empty() || words.empty()) {
            return res;
        }

        unordered_map<string, int> ht;
        for (const auto& w : words) {
            ht[w]++;
        }

        int len = words[0].length();
        for (int i = 0, j = 0; i < s.length() - words.size() * len + 1; i++) {
            unordered_map<string, int> counting;
            for (j = 0; j < words.size(); j++) {
            	string word = s.substr(i + j * len, len);
                if (++counting[word] > ht[word]) {
                    break;
                }
            }
            if (j == words.size()) {
                res.push_back(i);
            }
        }

        return res;
    }
};
