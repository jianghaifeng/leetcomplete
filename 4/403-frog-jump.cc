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


    bool canCross(vector<int>& stones) {
        unordered_map<int, unordered_set<int>> m;
        for (auto i : stones) m[i] = {};
        if (stones[1] != 1) return false;
        m[1].insert(1);
        for (int i=1; i<stones.size(); i++) {
            int n = stones[i];
            for (auto k : m[n]) {
                if (k > 1 && m.count(n+k-1) > 0) m[n+k-1].insert(k-1);
                if (m.count(n+k)) m[n+k].insert(k);
                if (m.count(n+k+1)) m[n+k+1].insert(k+1);
                if (stones.back() == n+k-1 || stones.back() == n+k || stones.back() == n+k+1) return true;
            }
        }
        return m[stones.back()].size() > 0;
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
        vector<int> stones = {0,1,3,5,6,8,12,17};
        EXPECT_EQ(true, s.canCross(stones));
    }

    TEST_F(SolutionTest, t2) {
        vector<int> stones = {0,1,2,3,4,8,9,11};
        EXPECT_EQ(false, s.canCross(stones));
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
