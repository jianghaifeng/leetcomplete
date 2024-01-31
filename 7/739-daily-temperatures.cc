#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:

    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<pair<int,int>> v;
        vector<int> ans(temperatures.size());
        for (int i=0; i<temperatures.size(); i++) {
            while (!v.empty() && v.back().first < temperatures[i]) {
                ans[v.back().second] = i - v.back().second;
                v.pop_back();
            }
            v.push_back({temperatures[i], i});
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
    vector<int> v = {73,74,75,71,69,72,76,73};
    EXPECT_THAT(s.dailyTemperatures(v), ::testing::ElementsAre(1,1,4,2,1,1,0,0));
}

TEST_F(SolutionTest, t2) {
    vector<int> v = {30,40,50,60};
    EXPECT_THAT(s.dailyTemperatures(v), ::testing::ElementsAre(1,1,1,0));
}

TEST_F(SolutionTest, t3) {
    vector<int> v = {30,60,90};
    EXPECT_THAT(s.dailyTemperatures(v), ::testing::ElementsAre(1,1,0));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
