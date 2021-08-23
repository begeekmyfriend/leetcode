#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<string> m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    vector<string> letterCombinations(string digits)
    {
        solve(0, "", digits);
        return ans;
    }
    void solve(int i, string path, string digits)
    {
        if (i >= digits.size())
        {
            if (path.size() > 0)
                ans.push_back(path);
            return;
        }
        for (auto c : m[digits[i] - '0'])
        {
            path += c;
            solve(i + 1, path, digits);
            path.pop_back();
        }
    }
};

int main()
{
    cout << "Enter A string : ";
    string s;
    cin >> s;
    Solution sol;
    // vector<string> ans = sol.letterCombinations(s) ;
    for (auto str : sol.letterCombinations(s))
    {
        cout << str << " ";
    }
    return 0;
}