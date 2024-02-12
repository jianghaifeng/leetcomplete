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

    vector<int> calcNext(vector<int>& pat) {
        vector<int> next(pat.size(), 0);
        for (int i=1, j=0; i<pat.size(); i++) {
            while (j > 0 && pat[i] != pat[j]) j = next[j-1];
            if (pat[i] == pat[j]) j++;
            next[i] = j;
        }
        return next;
    }

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        for (int i=0; i<nums.size()-1; i++) {
            if (nums[i] == nums[i+1]) nums[i] = 0;
            else if (nums[i] > nums[i+1]) nums[i] = -1;
            else nums[i] = 1;
        }
        nums.pop_back();
        auto next = calcNext(pattern);
        int ans = 0;
        for (int i=0, j=0; i<nums.size(); i++) {
            while (j > 0 && nums[i] != pattern[j]) j = next[j-1];
            if (nums[i] == pattern[j]) j++;
            if (j == pattern.size()) ans++, j = next[j-1];
        }
        return ans;
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
    vector<int> nums = {1,2,3,4,5,6};
    vector<int> pattern = {1,1};
    EXPECT_EQ(4, s.countMatchingSubarrays(nums, pattern));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {1,4,4,1,3,5,5,3};
    vector<int> pattern = {1,0,-1};
    EXPECT_EQ(2, s.countMatchingSubarrays(nums, pattern));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
