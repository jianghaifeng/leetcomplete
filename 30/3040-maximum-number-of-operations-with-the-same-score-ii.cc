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


    int helper(vector<int>& v, vector<vector<int>>& dp, int l, int r, int t) {
        if (r == l) return 0;
        if (l+1 == r) return v[l]+v[r] == t;
        if (dp[l][r] >= 0) return dp[l][r];
        dp[l][r] = 0;
        if (v[l]+v[l+1] == t) dp[l][r] = max(dp[l][r], 1+helper(v, dp, l+2, r, t));
        if (v[l]+v[r] == t) dp[l][r] = max(dp[l][r], 1+helper(v, dp, l+1, r-1, t));
        if (v[r]+v[r-1] == t) dp[l][r] = max(dp[l][r], 1+helper(v, dp, l, r-2, t));
        return dp[l][r];
    }

    int fa(vector<int>& nums) {
        int n = nums.size();
        int t = nums[0] + nums[1];
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return helper(nums, dp, 2, n-1, t);
    }
    
    int fb(vector<int>& nums) {
        int n = nums.size();
        int t = nums[0] + nums[n-1];
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
        return helper(nums, dp, 1, n-2, t);
    }
    
    int fc(vector<int>& nums) {
        int n = nums.size();
        int t = nums[n-1] + nums[n-2];
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
        return helper(nums, dp, 0, n-3, t);
    }

    int maxOperations(vector<int>& nums) {
        if (nums.size() == 2) return 1;
        int a = fa(nums), b = fb(nums), c = fc(nums);
        return max(a, max(b, c)) + 1;
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
    vector<int> input = {3,2,1,2,3,4};
    EXPECT_EQ(3, s.maxOperations(input));
}

TEST_F(SolutionTest, t2) {
    vector<int> input = {3,2,6,1,4};
    EXPECT_EQ(2, s.maxOperations(input));
}



int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
