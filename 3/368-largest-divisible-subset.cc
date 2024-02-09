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


    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int maxi = 0;
        vector<pair<int,int>> vp = {{-1, 1}};
        for (int i=1; i<nums.size(); i++) {
            int maxj = -1;
            for (int j=i-1; j>=0; j--) {
                if (nums[i] % nums[j]) continue;
                if (maxj == -1 || vp[j].second > vp[maxj].second) maxj = j;
            }
            if (maxj == -1) vp.push_back({-1, 1});
            else vp.push_back({maxj, vp[maxj].second+1});
            if (vp.back().second > vp[maxi].second) maxi = i;
        }
        vector<int> ans;
        while (maxi >= 0) {
            ans.push_back(nums[maxi]);
            maxi = vp[maxi].first;
        }
        reverse(ans.begin(), ans.end());
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
    vector<int> input = {1,2,3};
    EXPECT_THAT(s.largestDivisibleSubset(input), testing::ElementsAre(1,2));
}

TEST_F(SolutionTest, t2) {
    vector<int> input = {1,2,4,8};
    EXPECT_THAT(s.largestDivisibleSubset(input), testing::ElementsAre(1,2,4,8));
}

TEST_F(SolutionTest, t3) {
    vector<int> input = {4,8,10,240};
    EXPECT_THAT(s.largestDivisibleSubset(input), testing::ElementsAre(4,8,240));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
