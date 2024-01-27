#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:

    const int mod=1e9+7;
    using LL = long long;

    int kInversePairs(int n, int k) {
        if (n < 1) return 0;
        vector<LL> v(k+1, 0); v[0] = 1;
        for (int i=2; i<=n; i++) {
            vector<LL> tmp(k+1,0); tmp[0] = 1;
            for (int j=1; j<=k; j++) {
                tmp[j] = (tmp[j-1] + v[j]) % mod;
                if (j >= i) tmp[j] = (mod + tmp[j] - v[j-i]) % mod;
            }
            swap(tmp, v);
        }
        return v[k];
    }

    int kInversePairs1(int n, int k) {
        vector<vector<LL>> dp(n+1, vector<LL>(k+1, -1));
        for (int i=0; i<=k; i++) dp[0][i] = dp[1][i] = 0;
        dp[1][0] = 1;
        return dfs(dp, n, k);
    }

    int dfs(vector<vector<LL>>& dp, int n, int k) {
        if (dp[n][k] >= 0) return dp[n][k];
        dp[n][k] = 0;
        for (int i=k; i>=max(0, k-n+1); i--) {
            dp[n][k] = (dp[n][k] + dfs(dp, n-1, i)) % mod;
        }
        return dp[n][k];
    }
};

/*


   dp[2][1] = 1

   dp[n][k] = dp[n-1][k] + dp[n-1][k-1] + ... + dp[n-1][max(0,k-n+1)];
   dp[n][k-1] = dp[n-1][k-1] + dp[n-1][k-2] + ... + dp[n-1][max(0, k-1-n+1)];

   dp[i][j] = dp[i-1][j] + ... dp[i-1][max(0, j-i+1)];
   dp[i][j-1] = dp[i-1][j-1] + ... dp[i-1][max(0, j-1-i+1];

   tmp[k] = tmp[k-1] + v[k];
   if (k-1 >= n-1) tmp[k] -= v[k-n];


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
    EXPECT_EQ(1, s.kInversePairs(3,0));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(2, s.kInversePairs(3,1));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ(708106253, s.kInversePairs(78,153));
}

TEST_F(SolutionTest, t4) {
    EXPECT_EQ(563044139, s.kInversePairs(30,46));
}

TEST_F(SolutionTest, t5) {
    EXPECT_EQ(530431936, s.kInversePairs(35,29));
}

TEST_F(SolutionTest, t6) {
    EXPECT_EQ(3836, s.kInversePairs(8,14));
}

TEST_F(SolutionTest, t7) {
    EXPECT_EQ(51684206, s.kInversePairs(998,786));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
