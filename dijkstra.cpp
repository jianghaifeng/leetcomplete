#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> shortestPaths(int n, vector<vector<int>>& edges) {
        vector<int> ans(n, INT_MAX);
        vector<unordered_map<int,int>> g(n);
        for (auto e : edges) g[e[0]][e[1]] = g[e[1]][e[0]] = e[2];
        vector<bool> done(n);
        ans[0] = 0;
        done[0] = true;
        int last = 0;
        while (true) {
            for (auto p : g[last]) {
                if (done[p.first]) continue;
                if (ans[p.first] > ans[last]+p.second) ans[p.first] = ans[last]+p.second;
            }
            int minPath=INT_MAX;
            for (int i=1; i<n; i++) {
                if (done[i]) continue;
                if (ans[i]<minPath) minPath=ans[i], last=i;
            }
            if (minPath==INT_MAX) break;
            done[last]=true;
        }

        return ans;
    }
};

void print(vector<int>& v) {
    for (auto i : v) cout << i << ",";
    cout << endl;
}
int main() {
    vector<vector<int>> edges = {
        {0, 1, 4},
        {0, 7, 8},
        {1, 2, 8},
        {1, 7, 11},
        {2, 3, 7},
        {2, 8, 2},
        {2, 5, 4},
        {3, 4, 9},
        {3, 5, 14},
        {4, 5, 10},
        {5, 6, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 8, 7}
    };

    Solution s;
    auto ans = s.shortestPaths(9, edges);
    print(ans);
}
