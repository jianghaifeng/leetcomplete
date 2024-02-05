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

    int eq(string& s, int i, int j, int k) {
        int ik=i*k, jk=j*k;
        for (int t=0; t<k && ik+t<s.length(); t++) {
            if (s[ik+t] != s[jk+t]) return false;
        }
        return true;
    }

    vector<int> calc(string& s, int k) {
        int len = (s.length() + k - 1) / k;
        vector<int> next(len);
        for (int i=1, j=0; i<len; i++) {
            while (j > 0 && !eq(s, i, j, k)) j = next[j-1];
            if (eq(s, i, j, k)) j++;
            next[i] = j;
        }
        return next;
    }

    int minimumTimeToInitialState(string word, int k) {
        vector<int> next = calc(word, k);
        return next.size() - next.back();
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
    EXPECT_EQ(4, s.minimumTimeToInitialState("abcbabcd", 2));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ(1, s.minimumTimeToInitialState("abacaba", 4));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ(2, s.minimumTimeToInitialState("abacaba", 3));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
