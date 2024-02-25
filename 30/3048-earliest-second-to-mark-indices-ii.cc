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
    using LL = long long;
    
    bool check(vector<int>& nums, vector<int>& changeIndices, vector<int> lastIndex) {
        sort(lastIndex.begin(), lastIndex.end());
        int spaces = 0, last = -1;
        for (auto i : lastIndex) {
            int t = changeIndices[i] - 1;
            spaces = spaces + i - last - nums[t] - 1;
            if (spaces < 0) return false;
            last = i;
        }
        return true;
    }
    
//     vector<int> getLatest(vector<vector<int>>& indexes, int k) {
//         vector<int> ans;
//         for (auto v : indexes) {
//             auto it = upper_bound(v.begin(), v.end(), k);
//             --it;
//             ans.push_back(*it);
//         }
//         return ans;
//     }
    
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size();
        LL sum = accumulate(nums.begin(), nums.end(), 0L);
        if (sum + n > changeIndices.size()) return -1;
        vector<int> vLast(n,-1);
        unordered_set<int> s;
        for (int i=0; i<changeIndices.size(); i++) {
            vLast[changeIndices[i]-1] = i;
            s.insert(changeIndices[i]);
            if (s.size() == n && check(nums,changeIndices,vLast)) {
                return i+1;
            }
        }
        return -1;
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
    vector<int> nums = {2,2,0};
    vector<int> changeIndices = {2,2,2,2,3,2,2,1};
    EXPECT_EQ(8, s.earliestSecondToMarkIndices(nums, changeIndices));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {1,3};
    vector<int> changeIndices = {1,1,1,2,1,1,1};
    EXPECT_EQ(6, s.earliestSecondToMarkIndices(nums, changeIndices));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {0,1};
    vector<int> changeIndices = {2,2,2};
    EXPECT_EQ(-1, s.earliestSecondToMarkIndices(nums, changeIndices));
}

TEST_F(SolutionTest, t4) {
    vector<int> nums = {0,2};
    vector<int> changeIndices = {2,1,2,2,1};
    EXPECT_EQ(4, s.earliestSecondToMarkIndices(nums, changeIndices));
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
