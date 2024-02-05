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
    int numberOfPairs(vector<vector<int>>& points) {
        int ans = 0;
        vector<vector<int>> vx(51);
        for (auto p : points) vx[p[0]].push_back(p[1]);
        for (int i=0; i<51; i++) {
            if (vx[i].empty()) continue;
            sort(vx[i].begin(), vx[i].end());
        }
        for (int i=0; i<51; i++) {
            for (int j=0; j<vx[i].size(); j++) {
                int last = -1;
                if (j > 0) last = vx[i][j-1], ans++;
                for (int k=i+1; k<51; k++) {
                    if (vx[k].empty()) continue;
                    auto it = upper_bound(vx[k].begin(), vx[k].end(), vx[i][j]);
                    if (it == vx[k].begin()) continue;
                    --it;
                    if (*it > last) last = *it, ans++;
                }
            }
        }
        return ans;
    }
};

/*
    *
          *
        * 
            *

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
    vector<vector<int>> v = {{1,1},{2,2},{3,3}};
    EXPECT_EQ(0, s.numberOfPairs(v));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> v = {{6,2},{4,4},{2,6}};
    EXPECT_EQ(2, s.numberOfPairs(v));
}

TEST_F(SolutionTest, t3) {
    vector<vector<int>> v = {{3,1},{1,3},{1,1}};
    EXPECT_EQ(2, s.numberOfPairs(v));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
