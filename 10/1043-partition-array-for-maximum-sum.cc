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

    int helper(vector<int>& dp, vector<int>& arr, int n, int k) {
        if (n == arr.size()) return 0;
        if (dp[n] >= 0) return dp[n];
        dp[n] = 0;
        int maxi = 0;
        for (int len=0; len<k; len++) {
            if (n+len == arr.size()) break;
            maxi = max(maxi, arr[n+len]);
            dp[n] = max(dp[n], maxi*(len+1) + helper(dp, arr, n+len+1, k));
        }
        return dp[n];
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> dp(arr.size(), -1);
        return helper(dp, arr, 0, k);
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
    vector<int> input = {1,15,7,9,2,5,10};
    EXPECT_EQ(84, s.maxSumAfterPartitioning(input, 3));
}

TEST_F(SolutionTest, t2) {
    vector<int> input = {1,4,1,5,7,3,6,1,9,9,3};
    EXPECT_EQ(83, s.maxSumAfterPartitioning(input, 4));
}

TEST_F(SolutionTest, t3) {
    vector<int> input = {1};
    EXPECT_EQ(1, s.maxSumAfterPartitioning(input, 1));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
