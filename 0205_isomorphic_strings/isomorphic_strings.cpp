#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string mp(string s)
    {
        map<char, int> m;
        string ans = "";
        for (auto c : s)
        {
            if (m.find(c) == m.end())
            {
                m[c] = m.size();
            }
            ans += m[c];
        }
        return ans;
    }
    bool isIsomorphic(string s, string t)
    {
        if (mp(s) == mp(t))
        {
            return true;
        }
        return false;
    }
};

int main()
{
    string s, t;
    cout << "Enter 2 Strings : ";
    cin >> s >> t;
    Solution sol;
    if (sol.isIsomorphic(s, t))
    {
        cout << "True";
    }
    else
    {
        cout << "False";
    }
}