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

    using LL = long long;
    using PLI = pair<LL, int>;
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());
        vector<int> cnt(n);
        priority_queue<int, vector<int>, greater<int>> rooms;
        for (int i=0; i<n; i++) rooms.push(i);
        auto comp = [](PLI& p1, PLI& p2) {
            return p1.first > p2.first;
        };
        priority_queue<PLI, vector<PLI>, decltype(comp)> inuse(comp);
        LL t = 0;
        for (auto m : meetings) {
            t = max((LL)m[0], t);
            if (rooms.empty()) t = max(t, inuse.top().first);
            while (!inuse.empty() && inuse.top().first <= t) {
                rooms.push(inuse.top().second);
                inuse.pop();
            }
            int roomId = rooms.top(); rooms.pop();
            cnt[roomId]++;
            inuse.push({t+m[1]-m[0], roomId});
        }
        int ans = 0;
        for (int i=1; i<n; i++) {
            if (cnt[i] > cnt[ans]) ans = i;
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
    vector<vector<int>> meetings = {{0,10},{1,5},{2,7},{3,4}};
    EXPECT_EQ(0, s.mostBooked(2, meetings));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> meetings = {{1,20},{2,10},{3,5},{4,9},{6,8}};
    EXPECT_EQ(1, s.mostBooked(3, meetings));
}

TEST_F(SolutionTest, t3) {
    vector<vector<int>> meetings = {{0,10},{1,2},{12,14},{13,15}};
    EXPECT_EQ(0, s.mostBooked(2, meetings));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
