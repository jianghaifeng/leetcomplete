#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:

    int minGroups(vector<vector<int>>& intervals) {
        priority_queue<int, vector<int>, greater<>> q;
        sort(intervals.begin(), intervals.end());
        for (auto itv : intervals) {
            if (!q.empty() && q.top() < itv[0]) q.pop();
            q.push(itv[1]);
        }
        return q.size();
    }

};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    vector<vector<int>> intv = {{5,10},{6,8},{1,5},{2,3},{1,10}};
    EXPECT_EQ(3, s.minGroups(intv));
}

TEST_F(SolutionFixture, t2) {
    vector<vector<int>> intv = {{1,3},{5,6},{8,10},{11,13}};
    EXPECT_EQ(1, s.minGroups(intv));
}

TEST_F(SolutionFixture, t3) {
}

TEST_F(SolutionFixture, t4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
