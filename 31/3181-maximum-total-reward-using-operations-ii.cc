#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());
        bitset<100001> dp(1);
        for (auto i : rewardValues) {
            int shift = dp.size() - i;
            dp |= dp << shift >> shift << i;
        }
        int ans = 0;
        for (int i=rewardValues.back()*2-1;; i--) {
            if (dp.test(i)) return i;
        }
    }
};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    vector<int> v = {1,1,3,3};
    EXPECT_EQ(4, s.maxTotalReward(v));
}

TEST_F(SolutionFixture, t2) {
    vector<int> v = {1,6,4,3,2};
    EXPECT_EQ(11, s.maxTotalReward(v));
}

TEST_F(SolutionFixture, t3) {
}

TEST_F(SolutionFixture, t4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
