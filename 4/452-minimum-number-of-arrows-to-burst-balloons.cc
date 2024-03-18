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

using namespace std;

class Solution {
public:

    int findMinArrowShots(vector<vector<int>>& points) {
        int ans = 0, i = 0;
        sort(points.begin(), points.end());
        while (i < points.size()) {
            int l = points[i][0], r = points[i][1];
            while (++i < points.size() && points[i][0] <= r) {
                l = points[i][0];
                r = min(r, points[i][1]);
            }
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
    vector<vector<int>> points = {{10,16},{2,8},{1,6},{7,12}};
    EXPECT_EQ(2, s.findMinArrowShots(points));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> points = {{1,2},{3,4},{5,6},{7,8}};
    EXPECT_EQ(4, s.findMinArrowShots(points));
}

TEST_F(SolutionTest, t3) {
    vector<vector<int>> points = {{1,2},{2,3},{3,4},{4,5}};
    EXPECT_EQ(2, s.findMinArrowShots(points));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
