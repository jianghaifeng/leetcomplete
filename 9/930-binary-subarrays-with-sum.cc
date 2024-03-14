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

    int slip(vector<int>& nums, int i) {
        if (i == nums.size()) return i;
        i++;
        while (i < nums.size() && nums[i] == 0) i++;
        return i;
    }

    int sum(vector<int>& nums, int goal) {
        int l = 0, r = 0, ans = 0;
        while (l < nums.size()) {
            if (nums[l] == 1) goal--;
            if (goal == 0) break;
            l++;
        }
        r = slip(nums, l);
        ans += r - l;
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == 1) {
                l = r;
                r = slip(nums, l);
            }
            ans += r - l;
        }
        return ans;
    }
    
    int sum0(vector<int>& nums) {
        int ans = 0, last = -1;
        for (int i=0; i<=nums.size(); i++) {
            if (i == nums.size() || nums[i] == 1) {
                ans += (i - last - 1) * (i - last) / 2, last = i;
            }
        }
        return ans;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        if (goal == 0) return sum0(nums);
        return sum(nums, goal);
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
    vector<int> nums = {1,0,1,0,1};
    EXPECT_EQ(4, s.numSubarraysWithSum(nums, 2));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {0,0,0,0,0};
    EXPECT_EQ(15, s.numSubarraysWithSum(nums, 0));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {1,1,0,1,1,1,1,1};
    EXPECT_EQ(1, s.numSubarraysWithSum(nums, 0));
}


TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
