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
    using LL = long long;
    void calc(vector<LL>& res, int a1, int a2, int b1, int b2) {
        int mod = 1e9+7;
        for (int i=a1; i<=a2; i++) {
            vector<LL> tmp(res.size());
            for (int j=b1; j<=b2; j++) {
                for (int k=j; k>=j-i&&k>=0; k--) tmp[j] = (tmp[j] + res[k]) % mod;
            }
            swap(tmp, res);
        }
    }

    int numberOfPermutations(int n, vector<vector<int>>& rq) {
        sort(rq.begin(), rq.end());
        int pos = 0;
        if (rq[0][0] == 0) {
            if (rq[0][1] != 0) return 0;
            pos++;
        }
        vector<LL> res(401);
        res[0] = 1;
        int last0 = 0, last1 = 0;
        for (; pos < rq.size(); pos++) {
            int a = rq[pos][0], b = rq[pos][1];
            if (b < last1) return 0;
            calc(res, last0+1, a-1, last1, b);
            calc(res, a, a, b, b);
            last0 = a;
            last1 = b;
        }
        return res[rq.back()[1]];
    }
};


/*
c[i][j] = c[i-1][j] + c[i-1][j-1] + ... + c[i-1][j-i]
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
    vector<vector<int>> req = {{0,0},{2,2}};
    EXPECT_EQ(2, s.numberOfPermutations(3, req));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> req = {{0,0},{1,1},{2,2}};
    EXPECT_EQ(1, s.numberOfPermutations(3, req));
}

TEST_F(SolutionTest, t3) {
    vector<vector<int>> req = {{0,0},{1,0}};
    EXPECT_EQ(1, s.numberOfPermutations(2, req));
}

TEST_F(SolutionTest, t4) {
    vector<vector<int>> req = {{4,5},{6,10},{14,53},{0,0}};
    EXPECT_EQ(393161917, s.numberOfPermutations(15, req));

}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
