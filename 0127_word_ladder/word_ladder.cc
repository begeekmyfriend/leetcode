#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) {
            return 0;
        }

        // double BFS
        int step = 1;
        unordered_set<string> s1, s2, tmp, visited;
        s1.insert(beginWord);
        s2.insert(endWord);
        while (!s1.empty() && !s2.empty()) {
            if (s1.size() > s2.size()) {
                tmp = s1;
                s1 = s2;
                s2 = tmp;
            }
            tmp.clear();

            for (auto str : s1) {
                if (s2.count(str)) {
                    return step;
                }
                if (!visited.count(str)) {
                    visited.insert(str);
                }

                for (int i = 0; i < str.length(); i++) {
                    char o = str[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == o) continue;
                        str[i] = c;
                        if (dict.count(str) && !visited.count(str)) {
                            tmp.insert(str);
                        }
                    }
                    str[i] = o;
                }
            }

            // update
            s1 = tmp;
            step++;
        }
        return 0;
    }
};
