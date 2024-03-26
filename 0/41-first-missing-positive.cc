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
    
    void propagate(vector<int>& nums, int i) {
        while (nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i]-1] != nums[i]) {
            swap(nums[i], nums[nums[i]-1]);
        }
    }

    int firstMissingPositive(vector<int>& nums) {
        for (int i=0; i<nums.size(); i++) {
            propagate(nums, i);
        }
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] != i + 1) return i+1;
        }
        return nums.size() + 1;
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
    vector<int> nums = {1,2,0};
    EXPECT_EQ(3, s.firstMissingPositive(nums));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {3,4,-1,1};
    EXPECT_EQ(2, s.firstMissingPositive(nums));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {7,8,9,11,12};
    EXPECT_EQ(1, s.firstMissingPositive(nums));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
