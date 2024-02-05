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

    int returnToBoundaryCount(vector<int>& nums) {
        int sum = 0, ans = 0;
        for (auto i : nums) {
            sum += i;
            if (sum == 0) ans++;
        }
        return ans;
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
    vector<int> v = {2,3,-5};
    EXPECT_EQ(1, s.returnToBoundaryCount(v));
}

TEST_F(SolutionTest, t2) {
    vector<int> v = {3,2,-3,-4};
    EXPECT_EQ(0, s.returnToBoundaryCount(v));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
