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


    bool more(const vector<int>& v1, const vector<int>& v2, int a) {
        for (int i=0; i<a; i++) {
            if (v1[i] < v2[i]) return false;
        }
        return true;
    }

    bool isTransformable(string s, string t) {
        vector<queue<vector<int>>> v(10);
        vector<int> pre0(10);

        for (auto c : s) {
            int a = c-'0';
            pre0[a]++;
            v[a].push(pre0);
        }

        vector<int> pre(10);
        for (auto c : t) {
            int a = c-'0';
            pre[a]++;
            if (v[a].empty()) return false;
            if (!more(pre, v[a].front(), a)) return false;
            v[a].pop();
        }
        for (int i=0; i<10; i++) {
            if (!v[i].empty()) return false;
        }
        
        return true;
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
    EXPECT_TRUE(s.isTransformable("84532", "34852"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_TRUE(s.isTransformable("34521", "23415"));
}

TEST_F(SolutionTest, t3) {
    EXPECT_FALSE(s.isTransformable("12345", "12435"));
}

TEST_F(SolutionTest, t4) {
    EXPECT_FALSE(s.isTransformable("12345", "16435"));
}

TEST_F(SolutionTest, t5) {
    EXPECT_FALSE(s.isTransformable("1234583765333", "1234658375333"));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
