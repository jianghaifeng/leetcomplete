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

    int countSubstrings(string s) {
        int ans = 0;
        vector<int> last, cur;
        for (int i=0; i<s.length(); i++) {
            cur.push_back(i);
            if (i > 0 && s[i] == s[i-1]) cur.push_back(i-1);
            for (auto j : last) {
                if (j > 0 && s[i] == s[j-1]) cur.push_back(j-1);
            }
            ans += cur.size();
            swap(last, cur);
            cur.clear();
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
    EXPECT_EQ(3, s.countSubstrings("abc"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(6, s.countSubstrings("aaa"));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
