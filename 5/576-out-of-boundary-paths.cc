#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:

    using LL = long long;
    using vvvi = vector<vector<vector<LL>>>;
    const int mod=1e9+7;
    int row, col;

    LL dfs(vvvi& dp, int i, int j, int k) {
        if (dp[i][j][k] >= 0) return dp[i][j][k];
        dp[i][j][k] = 0;
        vector<pair<int,int>> vn = {
            {i+1,j}, {i-1,j}, {i,j+1}, {i,j-1}
        };
        for (auto n : vn) {
            if (n.first>=0 && n.first<row && n.second>=0 && n.second<col) {
                dp[i][j][k] = (dp[i][j][k] + dfs(dp, n.first, n.second, k-1)) % mod;
            }
        }
        return dp[i][j][k];
    }

    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        row = m, col = n;
        vvvi dp(m, vector<vector<LL>>(n, vector<LL>(maxMove+1, -1)));
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                dp[i][j][0] = 0;
                dp[i][j][1] = (i==0) + (j==0) + (i==m-1) + (j==n-1);
            }
        }
        LL ans = 0;
        for (int i=1; i<=maxMove; i++) {
            ans = (ans + dfs(dp, startRow, startColumn, i)) % mod;
        }
        return ans;
    }
};

/*
 
*/


class SolutionTest : public ::testing::Test {
public:
    virtual void setUp() {
    }
    virtual void tearDown() {
    }

    Solution s;
};

TEST_F(SolutionTest, t1) {
    EXPECT_EQ(6, s.findPaths(2, 2, 2, 0, 0));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(12, s.findPaths(1, 3, 3, 0, 1));
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
