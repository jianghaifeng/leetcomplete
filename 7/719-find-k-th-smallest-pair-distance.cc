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

    int count(vector<int>& v, int x) {
        int ans = 0;
        for (int l=0, r=0; l<v.size(); l++) {
            while (r < v.size() && v[r] - v[l] <= x) r++;
            ans += r - l - 1;
        }
        return ans;
    }

    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = nums.back() - nums[0];
        while (lo < hi) {
            int m = (lo + hi) / 2;
            int c = count(nums, m);
            if (c >= k) hi = m;
            else lo = m + 1;
        }
        return lo;
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
    vector<int> v = {1,3,1};
    EXPECT_EQ(0, s.smallestDistancePair(v, 1));
}

TEST_F(SolutionTest, t2) {
    vector<int> v = {1,1,1};
    EXPECT_EQ(0, s.smallestDistancePair(v, 2));
}

TEST_F(SolutionTest, t3) {
    vector<int> v = {1,6,1};
    EXPECT_EQ(5, s.smallestDistancePair(v, 3));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {
    InitGoogleTest();
    return RUN_ALL_TESTS();
}
