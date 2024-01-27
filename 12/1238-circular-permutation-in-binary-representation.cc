#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;
class Solution {
public:

    vector<int> circularPermutation(int n, int start) {
        vector<int> ans(1 << n);
        for (int i=0; i<n; i++) {
            int hi = (1<<i)-1, lo = hi+1;
            for (; hi>=0; hi--, lo++) ans[lo] = (1<<i) + ans[hi];
        }
        for (auto& i : ans) i = i ^ start;
        return ans;
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
    EXPECT_THAT(s.circularPermutation(2,3), testing::ElementsAre(3,2,0,1));
}

TEST_F(SolutionTest, t2) {
    EXPECT_THAT(s.circularPermutation(3,2), testing::ElementsAre(2, 3, 1, 0, 4, 5, 7, 6));
}

TEST_F(SolutionTest, t3) {
    EXPECT_THAT(s.circularPermutation(4,0), testing::ElementsAre(0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8));
}

TEST_F(SolutionTest, t4) {
    EXPECT_THAT(s.circularPermutation(4,15), testing::ElementsAre(15,14,12,13,9,8,10,11,3,2,0,1,5,4,6,7));
}

TEST_F(SolutionTest, t5) {
    EXPECT_THAT(s.circularPermutation(4,8), testing::ElementsAre(8,9,11,10,14,15,13,12,4,5,7,6,2,3,1,0));
}

TEST_F(SolutionTest, t6) {
    EXPECT_THAT(s.circularPermutation(4,1), testing::ElementsAre(1,0,2,3,7,6,4,5,13,12,14,15,11,10,8,9));
}

TEST_F(SolutionTest, t7) {
    EXPECT_THAT(s.circularPermutation(4,7), testing::ElementsAre(7,6,4,5,1,0,2,3,11,10,8,9,13,12,14,15));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}



