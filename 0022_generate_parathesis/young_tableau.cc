#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:
    vector<vector<int>> young_tableau(int n) {
        vector<vector<int>> res;
        dfs(n, 0, 0, res);
        return res;
    }

private:
    vector<char> stack;

    void dfs(int n, int l, int r, vector<vector<int>>& res) {
        if (stack.size() == 2 * n) {
            vector<int> sol(2 * n);
            for (int i = 0, j = 0, k = n; i < 2 * n; i++) {
                if (stack[i] == '(') {
                    sol[j++] = i + 1;
                } else {
                    sol[k++] = i + 1;
                }
            }
            res.push_back(sol);
        } else {
            if (l < n) {
                stack.push_back('(');
                dfs(n, l + 1, r, res);
                stack.pop_back();
            }

            if (r < l) {
                stack.push_back(')');
                dfs(n, l, r + 1, res);
                stack.pop_back();
            }
        }
    }
};

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    Solution *solution = new Solution();
    vector<vector<int>> res = solution->young_tableau(n);
    for (auto& v : res) {
        for (int i = 0; i < 2 * n; i++) {
            if (i == n) cout << endl;
            cout << v[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}
