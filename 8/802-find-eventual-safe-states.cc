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


    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> g(n), ans;
        vector<bool> safe(n);
        vector<vector<int>> v(n);
        queue<int> q;
        for (int i=0; i<n; i++) {
            if (graph[i].size() == 0) q.push(i);
            g[i] = graph[i].size();
            for (auto j : graph[i]) v[j].push_back(i);
        }
        while (!q.empty()) {
            int f = q.front(); q.pop();
            safe[f] = true;
            for (auto i : v[f]) {
                g[i]--;
                if (g[i] == 0) q.push(i);
            }
        }
        for (int i=0; i<n; i++) {
            if (safe[i]) ans.push_back(i);
        }
        return ans;
    }


};


/*

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
    vector<vector<int>> v = {{1,2},{2,3},{5},{0},{5},{},{}};
    EXPECT_THAT(s.eventualSafeNodes(v), ElementsAre(2,4,5,6));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> v = {{1,2,3,4},{1,2},{3,4},{0,4},{}};
    EXPECT_THAT(s.eventualSafeNodes(v), ElementsAre(4));
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
