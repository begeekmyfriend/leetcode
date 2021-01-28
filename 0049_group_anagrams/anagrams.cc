#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> ht;
        for (const auto& str : strs) {
            int counts[26] = { 0 };
            for (char c : str) {
                counts[c - 'a']++;
            }

            string key;
            for (int i : counts) {
                key.push_back('#');
                key.push_back(i + '0');
            }

            ht[key].push_back(str);
        }

        for (const auto& t : ht) {
            res.push_back(t.second);
        }
        return res;
    }
};
