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

using namespace std;

class Solution {
public:
    using LL = long long;
    pair<bool, LL> dfs(vector<int>& nums, vector<vector<int>>& g, int prev, int cur, int k, int& mini) {
        LL sum = 0;
        int other = nums[cur] ^ k;
        bool inv = false, rev = false;
        if (other > nums[cur]) inv = true, sum = other;
        else inv = false, sum = nums[cur];
        mini = min(mini, (int)abs(other - nums[cur]));
        for (auto next : g[cur]) {
            if (next == prev) continue;
            auto p = dfs(nums, g, cur, next, k, mini);
            if (!p.first) rev = !rev;
            sum += p.second;
        }
        return {inv == rev, sum};
    }

    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int mini = k;
        auto p = dfs(nums, g, -1, 0, k, mini);
        if (!p.first) return p.second - mini;
        return p.second;
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
    vector<int> nums = {1,2,1};
    vector<vector<int>> edges = {{0,1},{0,2}};
    EXPECT_EQ(6, s.maximumValueSum(nums, 3, edges));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {2,3};
    vector<vector<int>> edges = {{0,1}};
    EXPECT_EQ(9, s.maximumValueSum(nums, 7, edges));
}


TEST_F(SolutionTest, t3) {
    vector<int> nums = {7,7,7,7,7,7};
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{0,4},{0,5}};
    EXPECT_EQ(42, s.maximumValueSum(nums, 3, edges));
}

TEST_F(SolutionTest, t4) {
    vector<int> nums = {24,78,1,97,44};
    vector<vector<int>> edges = {{0,2},{1,2},{4,2},{3,4}};
    EXPECT_EQ(260, s.maximumValueSum(nums, 6, edges));
}

TEST_F(SolutionTest, t5) {
    vector<int> nums = {7,7,7,7,7,7};
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{0,4},{0,5}};
    EXPECT_EQ(6000000042, s.maximumValueSum(nums, 1000000000, edges));
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
