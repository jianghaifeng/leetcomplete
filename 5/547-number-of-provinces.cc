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

    int find(vector<int>& v, int a) {
        vector<int> tmp;
        while (v[a] != a) {
            tmp.push_back(a);
            a = v[a];
        }
        while (!tmp.empty()) v[tmp.back()] = a, tmp.pop_back();
        return a;
    }

    void merge(vector<int>& v, int a, int b) {
        int ra = find(v, a), rb = find(v, b);
        if (ra < rb) v[rb] = ra;
        else v[ra] = rb;
    }

    int findCircleNum1(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> v(n);
        for (int i=0; i<n; i++) v[i] = i;
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                if (isConnected[i][j] == 1) merge(v, i, j);
            }
        }
        unordered_set<int> s;
        for (int i=0; i<n; i++) s.insert(find(v, i));
        return s.size();
    }

    void bfs(vector<vector<int>>& isConnected, vector<bool>& mark, int i) {
        queue<int> q; q.push(i);
        mark[i] = true;
        while (!q.empty()) {
            int f = q.front(); q.pop();
            for (int i=0; i<isConnected.size(); i++) {
                if (!mark[i] && isConnected[f][i] == 1) q.push(i), mark[i] = true;
            }
        }
    }

    int findCircleNum2(vector<vector<int>>& isConnected) {
        int ans = 0;
        vector<bool> mark(isConnected.size());
        for (int i=0; i<isConnected.size(); i++) {
            if (mark[i]) continue;
            bfs(isConnected, mark, i);
            ans++;
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
    vector<vector<int>> isConnected = {{1,1,0},{1,1,0},{0,0,1}};
    EXPECT_EQ(2, s.findCircleNum1(isConnected));
    EXPECT_EQ(2, s.findCircleNum2(isConnected));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> isConnected = {{1,0,0},{0,1,0},{0,0,1}};
    EXPECT_EQ(3, s.findCircleNum1(isConnected));
    EXPECT_EQ(3, s.findCircleNum2(isConnected));
}

TEST_F(SolutionTest, t3) {
    vector<vector<int>> isConnected = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    EXPECT_EQ(1, s.findCircleNum1(isConnected));
    EXPECT_EQ(1, s.findCircleNum2(isConnected));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
