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

    int trap(vector<int>& height) {
        int maxIndex = max_element(height.begin(), height.end()) - height.begin();
        int ans = 0, last = height[0];
        for (int i=1; i<maxIndex; i++) {
            if (height[i] <= last) ans += last - height[i];
            else last = height[i];
        }
        last = height.back();
        for (int i=height.size()-2; i>maxIndex; i--) {
            if (height[i] <= last) ans += last - height[i];
            else last = height[i];
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
    vector<int> heights = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(6, s.trap(heights));
}

TEST_F(SolutionTest, t2) {
    vector<int> heights = {4,2,0,3,2,5};
    EXPECT_EQ(9, s.trap(heights));
}

TEST_F(SolutionTest, t3) {
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
