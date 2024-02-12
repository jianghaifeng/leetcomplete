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


    int majorityElement(vector<int>& nums) {
        int count = 0, ele = 0;
        for (auto i : nums) {
            if (count == 0) {
                ele = i;
                count = 1;
            } else if (i == ele) count++;
            else count--;
        }
        return ele;
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
    vector<int> input = {3,2,3};
    EXPECT_EQ(3, s.majorityElement(input));
}

TEST_F(SolutionTest, t2) {
    vector<int> input = {2,2,1,1,1,2,2};
    EXPECT_EQ(2, s.majorityElement(input));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
