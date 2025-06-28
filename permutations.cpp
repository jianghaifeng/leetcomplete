#include <iostream>
#include <vector>
#include <bit>

using namespace std;

class Solution {
public:
    void perm(string s) {
        vector<int> f(26), fr(26);
        for (auto c : s) f[c-'a']++;
        string res;
        auto put = [&](char c) -> bool {
            res.push_back(c);
            if (++fr[c-'a'] > f[c-'a']) return false;
            return true;
        };
        auto pop = [&](char c) {
            res.pop_back();
            fr[c-'a']--;
        };
        using DfsFunc = function<void()>;
        DfsFunc dfs;
        dfs = [&]() -> void {
            for (char c='a'; c<='z'; c++) {
                if (put(c)) {
                    cout << res << endl;
                    dfs();
                }
                pop(c);
            }
        };

        dfs();
    }
};

int main() {
    Solution s;
    s.perm("abc");
}

