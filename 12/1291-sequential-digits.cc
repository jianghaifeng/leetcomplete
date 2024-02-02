#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:

    int helper(int start, int len) {
        int ans = 0;
        while (--len >= 0) ans = ans * 10 + (start++);
        return ans;
    }

    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        for (int len=2; len<=9; len++) {
            for (int start=1; start<=10-len; start++) {
                int n = helper(start, len);
                if (n > high) break;
                if (n < low) continue;
                ans.push_back(n);
            }
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
    EXPECT_THAT(s.sequentialDigits(100,300), ::testing::ElementsAre(123,234));
}

TEST_F(SolutionTest, t2) {
    EXPECT_THAT(s.sequentialDigits(1000,13000), ::testing::ElementsAre(1234,2345,3456,4567,5678,6789,12345));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
