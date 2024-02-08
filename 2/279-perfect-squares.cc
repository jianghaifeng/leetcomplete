#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:

    int helper(vector<int>& dp, int n) {
        if (dp[n] >= 0) return dp[n];
        dp[n] = INT_MAX;
        for (int i=1; i*i <= n; i++) {
            dp[n] = min(dp[n], 1 + helper(dp, n - i*i));
        }
        return dp[n];
    }

    int numSquares(int n) {
        vector<int> dp(n+1, -1);
        dp[0] = 0;
        return helper(dp, n);
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
    EXPECT_EQ(3, s.numSquares(12));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(2, s.numSquares(13));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
