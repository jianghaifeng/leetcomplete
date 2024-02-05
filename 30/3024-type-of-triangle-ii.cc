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

    string triangleType(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums[0] + nums[1] <= nums[2]) return "none";
        if (nums[0] == nums[1] && nums[1] == nums[2]) return "equilateral";
        if (nums[0] == nums[1] || nums[1] == nums[2]) return "isosceles";
        return "scalene";
    }
    
};

/*

ADOBECODEBANC
i
      j

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
    vector<int> v = {3,3,3};
    EXPECT_EQ("equilateral", s.triangleType(v));
}

TEST_F(SolutionTest, t2) {
    vector<int> v = {3,4,5};
    EXPECT_EQ("scalene", s.triangleType(v));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
