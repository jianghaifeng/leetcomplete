#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:

    int sessionTime;
    vector<int> tasks;
    
    using LL = long long;

    int minSessions(vector<int>& tasks, int sessionTime) {
        this->sessionTime = sessionTime;
        this->tasks = tasks;
        int lo=1, hi=tasks.size()+1;
        while (lo < hi) {
            int m = (lo + hi) / 2;
            if (check(m)) hi = m;
            else lo = m+1;
        }
        return lo;
    }

    LL encode(int i, map<int,int>& m) {
        LL ans = i;
        for (auto [k, c] : m) {
            for (int i=0; i<c; i++) ans = (ans << 4) | k;
        }
        return ans;
    }

    pair<int, map<int,int>> decode(LL x, int n) {
        map<int,int> m;
        for (int i=0; i<n; i++) {
            m[x&15]++;
            x = x >> 4;
        }
        return {x, m};
    }

    bool helper(LL cur, int n, unordered_map<LL, bool>& um) {
        if (um.count(cur)) return um[cur];
        auto [index, m] = decode(cur, n);
        if (index == tasks.size()) return true;
        vector<int> tmp;
        for (auto [k, _] : m) {
            if (k+tasks[index] <= sessionTime) tmp.push_back(k);
        }
        for (auto k : tmp) {
            if (k+tasks[index] <= sessionTime) {
                m[k]--;
                m[k+tasks[index]]++;
                LL next = encode(index+1,m);
                if (helper(next, n, um)) return um[cur] = true;
                m[k]++;
                m[k+tasks[index]]--;
            }
        }
        return um[cur] = false;
    }

    bool check(int n) {
        if (n >= tasks.size()) return true;
        unordered_map<LL, bool> m;
        return helper(0, n, m);
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
    vector<int> v = {1,2,3};
    EXPECT_EQ(2, s.minSessions(v, 3));
}

TEST_F(SolutionTest, t2) {
    vector<int> v= {3,1,3,1,1};
    EXPECT_EQ(2, s.minSessions(v, 8));
}

TEST_F(SolutionTest, t3) {
    vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(1, s.minSessions(v, 15));
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
