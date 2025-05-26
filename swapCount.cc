#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;


class Solution {
public:

    int swapCount(vector<int>& v) {
        int n = v.size(), ans = 0;
        vector<int> pos(n);
        for (int i=0; i<n; i++) pos[v[i]] = i;
        for (int i=0; i<n; i++) {
            if (v[i] != i) {
                int other = pos[i];
                pos[v[i]] = other;
                swap(v[i], v[other]);
                ans++;
            }
        }
        return ans;
    }
};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    vector<int> arr = {1,0,2};
    EXPECT_EQ(1, s.swapCount(arr));
}

TEST_F(SolutionFixture, t2) {
    vector<int> arr = {1,2,0};
    EXPECT_EQ(2, s.swapCount(arr));
}

TEST_F(SolutionFixture, t3) {
}

TEST_F(SolutionFixture, t4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
