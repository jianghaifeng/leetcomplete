#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;


// LCP 04, binary graph, maximum link count, Hungarian algorithm
class Solution {
public:
    struct BinaryGraph {
        vector<vector<int>> g;
        vector<int> vis;
        vector<int> match;

        BinaryGraph(int n) {
            g.resize(n);
            vis.resize(n);
            match.resize(n, -1);
        }

        void add(int i, int j) {
            g[i].push_back(j);
        }

        /*
        1 - 2
          X
        4   3
        */

        void debug() {
            for (int i=0; i<g.size(); i++) {
                cout << i << ":";
                for (auto j : g[i]) cout << j << ",";
                cout << endl;
            }
        }

        bool dfs(int i) {
            vis[i] = 1;
            for (auto j : g[i]) {
                if (match[j] == -1) {
                    match[i] = j;
                    match[j] = i;
                    return true;
                }
            }
            for (auto j : g[i]) {
                if (vis[match[j]] == 0 && dfs(match[j])) {
                    match[i] = j;
                    match[j] = i;
                    return true;
                }
            }
            return false;
        }

        int solve() {
            int cnt = 0;
            for (int k=0; k<g.size(); k++) {
                fill(vis.begin(), vis.end(), 0);
                if (g[k].size() > 0 && dfs(k)) {
                    cnt++;
                }
            }
            return cnt;
        }
    };

    int domino(int n, int m, vector<vector<int>>& broken) {
        vector<vector<int>> grid(n, vector<int>(m));
        BinaryGraph bg(m*n);
        for (auto b : broken) grid[b[0]][b[1]] = 1;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if ((i+j) % 2 == 1) continue;
                if (grid[i][j] == 1) continue;
                if (i>0 && grid[i-1][j] == 0)
                    bg.add(i*m+j, (i-1)*m+j);
                if (i<n-1 && grid[i+1][j] == 0)
                    bg.add(i*m+j, (i+1)*m+j);
                if (j>0 && grid[i][j-1] == 0)
                    bg.add(i*m+j, i*m+j-1);
                if (j<m-1 && grid[i][j+1] == 0)
                    bg.add(i*m+j, i*m+j+1);
            }
        }
        // bg.debug();
        return bg.solve();
    }
};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    vector<vector<int>> broken = {
        {1,0}, {1,1}
    };
    EXPECT_EQ(2, s.domino(2, 3, broken));
}

TEST_F(SolutionFixture, t2) {
    vector<vector<int>> broken = {};
    EXPECT_EQ(4, s.domino(3, 3, broken));
}

TEST_F(SolutionFixture, t3) {
}

TEST_F(SolutionFixture, t4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
