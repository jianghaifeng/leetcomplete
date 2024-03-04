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

    vector<vector<int>> g, dist;
    vector<unordered_map<int,int>> v;
    int speed;

    void bfs(int prev, int cur) {
        for (int next : g[cur]) {
            if (next == prev) continue;
            pull(cur, next);
            v[cur][dist[cur][next]]++;
            for (auto p : v[next]) v[cur][(p.first + dist[cur][next])%speed] += p.second;
        } 
    }

    void bfs1(int prev, int cur, vector<int>& ans) {
        int a = v[cur][0];
        if (prev != -1) {
            auto m = v[prev];
            m[dist[prev][cur]]--;
            for (auto p : v[cur]) m[(p.first + dist[prev][cur]) % speed] -= p.second;
            for (auto p : m) v[cur][(p.first + dist[prev][cur]) % speed] += p.second;
            v[cur][dist[prev][cur]]++;
        }
        ans[cur] += a * (v[cur][0] - a);

        for (auto next : g[cur]) {
            if (next == prev) continue;
            int b = v[next][(speed - dist[cur][next])%speed];
            if (dist[cur][next] == 0) b++;
            ans[cur] += b * (v[cur][0] - b);
            calc(cur, next, ans);
        }
        ans[cur] /= 2;
    }

    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        int n = edges.size() + 1;
        speed = signalSpeed;
        g.resize(n);
        v.resize(n);
        dist.resize(n, vector<int>(n));
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2] % speed;
        }

        bfs(-1, 0);
        vector<int> ans(n);
        bfs1(-1, 0, ans);
        return ans;
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
    vector<vector<int>> edges = {{0,1,1},{1,2,5},{2,3,13},{3,4,9},{4,5,2}};
    EXPECT_THAT(s.countPairsOfConnectableServers(edges, 1), ElementsAre(0,4,6,6,4,0));
}

TEST_F(SolutionTest, t2) {
    vector<vector<int>> edges = {{0,6,3},{6,5,3},{0,3,1},{3,2,7},{3,1,6},{3,4,2}};
    EXPECT_THAT(s.countPairsOfConnectableServers(edges, 3), ElementsAre(2,0,0,0,0,0,2));
}

int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
