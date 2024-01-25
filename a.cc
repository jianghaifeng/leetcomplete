#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;


class Solution {
public:
    string s, t;

    int helper(vector<vector<int>>& dp, int i, int j) {
        if (dp[i][j] >= 0) return dp[i][j];
        dp[i][j] = dp[i-1][j-1];
        if (s[i] == t[j]) dp[i][j] = helper(dp, i-1, j-1) + 1;
        else dp[i][j] = max(helper(dp, i, j-1), helper(dp, i-1, j));
        return dp[i][j];
    }

    int longestCommonSubsequence(string text1, string text2) {
        s = text1, t = text2;
        int a = s.length(), b = t.length();
        vector<vector<int>> dp(a, vector<int>(b,-1));
        dp[0][0] = (s[0] == t[0]);
        for (int i=1; i<a; i++) 
            dp[i][0] = dp[i-1][0] || (s[i] == t[0]);
        for (int i=1; i<b; i++)
            dp[0][i] = dp[0][i-1] || (s[0] == t[i]);
        return helper(dp, a-1, b-1);
    }

};

/*
 
   dp[i][j] 

   i==j: dp[i][j] = dp[i-1][j-1] + 1;
   i!=j: dp[i][j] = max(dp[i-1][j], dp[i,j-1])


   top-down dp

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
    EXPECT_EQ(3, s.longestCommonSubsequence("abcde", "ace"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(3, s.longestCommonSubsequence("abc", "abc"));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ(0, s.longestCommonSubsequence("abc", "def"));
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
