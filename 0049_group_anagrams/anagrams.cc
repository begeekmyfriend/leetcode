#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> ht;
        for (const auto& str : strs) {
            int counts[26] = { 0 };
            for (const auto& s : str) {
                counts[s - 'a']++;
            }

            string key;
            for (const auto& c : counts) {
                key.push_back('#');
                key.push_back(c + '0');
            }

            ht[key].push_back(str);
        }

        for (const auto& t : ht) {
            res.push_back(t.second);
        }
        return res;
    }
};
