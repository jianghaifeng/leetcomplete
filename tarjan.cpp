#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<int> dfn, low, st, inst, ans;
    vector<vector<int>> g;
    int tot, cnt;
    vector<int> scc(int n, vector<vector<int>>& edges) {
        dfn.resize(n);
        low.resize(n);
        inst.resize(n);
        ans.resize(n+1);
        g.resize(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);
        }
        tot = 0;
        cnt = 0;
        tarjan(1);
        return ans;
    }
    
    void tarjan(int x) {
        dfn[x] = low[x] = ++tot;
        st.push_back(x), inst[x] = 1;
        for (int y : g[x]) {
            if (dfn[y] == 0) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
            } else if (inst[y]) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int y;
            ++cnt;
            do {
                y = st.back(); st.pop_back();
                inst[y] = 0;
                ans[y] = cnt;
            } while (x != y);
        }
    }
};

int main() {
    int n = 9;
    vector<vector<int>> edges = {
        {1,2}, {9,3}, {3,2},
        {1,4}, {3,1}, {4,5},
        {5,6}, {6,8}, {6,7},
        {5,7}, {8,5}, {8,7},
        {9,7}, {4,9}, {2,3}
    };
    Solution s;
    auto res = s.scc(n, edges);
    for (auto i : res) cout << i <<",";
    cout << endl;
    return 0;
}
