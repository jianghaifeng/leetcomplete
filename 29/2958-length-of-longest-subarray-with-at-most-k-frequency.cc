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

    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        int ans = 0;
        for (int i=0,j=0; j<nums.size(); j++) {
            m[nums[j]]++;
            while (m[nums[j]] > k) {
                m[nums[i++]]--;
            }
            ans = max(ans, j-i+1);
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
    vector<int> nums = {1,2,3,1,2,3,1,2};
    EXPECT_EQ(6, s.maxSubarrayLength(nums, 2));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {1,2,1,2,1,2,1,2};
    EXPECT_EQ(2, s.maxSubarrayLength(nums, 1));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {5,5,5,5,5,5,5};
    EXPECT_EQ(4, s.maxSubarrayLength(nums, 4));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
