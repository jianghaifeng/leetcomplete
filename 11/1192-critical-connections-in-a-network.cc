#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> dfn, low, st, inst, scc;
    vector<vector<int>> adj;
    unordered_set<long long> visited;
    int tot, cnt;

    void helper(int n, vector<vector<int>>& edges) {
        adj = vector<vector<int>>(n, vector<int>());
        adj.resize(n, vector<int>());
        for (auto e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        dfn = vector<int>(n);
        low = vector<int>(n);
        inst = vector<int>(n);
        scc = vector<int>(n);
        st.clear();
        visited.clear();
        tot = 0;
        cnt = 0;
    }

    bool check(int x, int y) {
        int l = min(x, y), h = max(x, y);
        long long n = (long long)l * 100001 + h;
        if (visited.count(n)) return true;
        visited.insert(n);
        return false;
    }

    void tarjan(int x) {
        dfn[x] = low[x] = ++tot;
        st.push_back(x);
        inst[x] = 1;
        for (int y : adj[x]) {
            if (check(x, y)) continue;
            if (dfn[y] == 0) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
            } else if (inst[y]) low[x] = min(low[x], dfn[y]);
        }

        if (low[x] == dfn[x]) {
            cnt++;
            while (true) {
                int y = st.back();
                scc[y] = cnt;
                st.pop_back();
                if (y == x) break;
            }
        }
    }

    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        helper(n, connections);
        tarjan(0);
        vector<vector<int>> ans;
        for (auto c : connections) {
            if (scc[c[0]] != scc[c[1]]) ans.push_back(c);
        }
        return ans;
    }

};


/*
c[i][j] = c[i-1][j] + c[i-1][j-1] + ... + c[i-1][j-i]
*/

using namespace testing;
class SolutionTest : public Test {
public:
    virtual void setUp() {
    }
    virtual void tearDown() {
    }

    Solution s;
};

TEST_F(SolutionTest, t1) {
    int n = 4;
    vector<vector<int>> conn = {{0,1},{1,2},{2,0},{1,3}};
    EXPECT_THAT(s.criticalConnections(n, conn), ElementsAre(UnorderedElementsAreArray({1,3})));
    EXPECT_THAT(s.criticalConnections(n, conn), ElementsAre(UnorderedElementsAre(3,1)));
}

TEST_F(SolutionTest, t2) {
    int n = 2;
    vector<vector<int>> conn = {{0,1}};
    EXPECT_THAT(s.criticalConnections(n, conn), ElementsAre(UnorderedElementsAreArray({0,1})));
}

TEST_F(SolutionTest, t3) {
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
