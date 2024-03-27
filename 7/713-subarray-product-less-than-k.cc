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
#include <queue>

using namespace std;

class Solution {
public:
    
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int ans = 0, i = 0, j = 0, prod = 1;
        while (i < nums.size()) {
            if (j < i) j = i, prod = 1;
            while (j < nums.size() && prod * nums[j] < k) prod *= nums[j++];
            ans += j-i;
            prod /= nums[i++];
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
    vector<int> nums = {10,5,2,6};
    EXPECT_EQ(8, s.numSubarrayProductLessThanK(nums,100));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {1,2,3};
    EXPECT_EQ(0, s.numSubarrayProductLessThanK(nums,0));
}

TEST_F(SolutionTest, t3) {
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
