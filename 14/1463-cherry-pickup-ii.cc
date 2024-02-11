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

    int get(vector<int>& last, int a, int b, int c) {
        int ans = -1;
        for (int i=a-1; i<=a+1; i++) {
            for (int j=b-1; j<=b+1; j++) {
                if (i >= 0 && i < c && j >= 0 && j < c && last[i*c+j] >= 0) {
                    ans = max(ans, last[i*c+j]);
                }
            }
        }
        return ans;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<int> last(c*c, -1), cur(c*c);
        last[c-1] = grid[0][0] + grid[0][c-1];
        for (int i=1; i<r; i++) {
            for (int k=0; k<c*c; k++) {
                int a=k/c, b=k%c;
                int d = get(last, a, b, c);
                if (d < 0) cur[k] = -1;
                else {
                    if (a == b) cur[k] = d + grid[i][a];
                    else cur[k] = d + grid[i][a] + grid[i][b];
                }
            }
            swap(last, cur);
        }
        return *max_element(last.begin(), last.end());
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
    vector<vector<int>> input = {
        {0,8,7,10,9,10,0,9,6},
        {8,7,10,8,7,4,9,6,10},
        {8,1,1,5,1,5,5,1,2},
        {9,4,10,8,8,1,9,5,0},
        {4,3,6,10,9,2,4,8,10},
        {7,3,2,8,3,3,5,9,8},
        {1,2,6,5,6,2,0,10,0}
    };
    EXPECT_EQ(96, s.cherryPickup(input));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
