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
        map<int, vector<int>> mx;
        for (auto p : points) mx[p[0]].push_back(p[1]);
        for (auto &p : mx) sort(p.second.begin(), p.second.end());
        for (auto &p : mx) {
            for (int i=0; i<p.second.size(); i++) {
                int last = INT_MIN;
                if (i > 0) last = p.second[i-1], ans++;
                for (auto &q : mx) {
                    if (q.first <= p.first) continue;
                    auto it = upper_bound(q.second.begin(), q.second.end(), p.second[i]);
                    if (it == q.second.begin()) continue;
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
