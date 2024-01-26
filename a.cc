#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:


    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        int m = (1 << n);
        vector<int> oneSessions;
        vector<int> dp(m, -1);
        dp[0] = 0;
        for (int i=1; i<m; i++) {
            int sum = 0;
            for (int j=0; j<n; j++) {
                if (((1<<j)&i)) sum += tasks[j];
                while (sum > sessionTime) break;
            }
            if (sum <= sessionTime) oneSessions.push_back(i);
        }
        return dfs(dp, oneSessions, m-1);
    }


    int dfs(vector<int>& dp, vector<int>& v, int k) {
        if (dp[k] >= 0) return dp[k];
        dp[k] = 15;
        for (auto i : v) {
            if ((i&k) == i) {
                dp[k] = min(dp[k], dfs(dp, v, (k&(~i)))+1);
            }
        }
        return dp[k];
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
    vector<int> v = {1,2,3};
    EXPECT_EQ(2, s.minSessions(v, 3));
}

TEST_F(SolutionTest, t2) {
    vector<int> v= {3,1,3,1,1};
    EXPECT_EQ(2, s.minSessions(v, 8));
}

TEST_F(SolutionTest, t3) {
    vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(1, s.minSessions(v, 15));
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
