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

    void put(vector<int>& bc, int n) {
        for (int i=0; i<31; i++) {
            if (((1<<i)&n) != 0) bc[i]++;
        }
    }

    void pop(vector<int>& bc, int n) {
        for (int i=0; i<31; i++) {
            if (((1<<i)&n) != 0) bc[i]--;
        }
    }

    int get(vector<int>& bc, int c) {
        int ans = 0;
        for (int i=0; i<31; i++) {
            if (bc[i] == c) ans |= (1 << i);
        }
        return ans;
    }
    
    long long countSubarrays(vector<int>& nums, int k) {
        int i = 0;
        long long ans = 0;
        while (i < nums.size()) {
            if ((nums[i] & k) == k) {
                int j = i;
                vector<int> bc(31);
                unordered_map<int,int> m;
                while (j < nums.size() && (nums[j] & k) == k) {
                    put(bc, nums[j]);
                    while (get(bc, j-i+1) == k) {
                        m[j]++;
                        pop(bc, nums[i++]);
                    }
                    j++;
                }
                for (auto [pos, cnt]: m) {
                    ans += (long long)(j - pos) * cnt;
                }
                i = j;
            } else i++;
        }
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
    vector<int> v = {1,1,1};
    EXPECT_EQ(6, s.countSubarrays(v, 1));
}

TEST_F(SolutionTest, t2) {
    vector<int> v = {1,1,2};
    EXPECT_EQ(3, s.countSubarrays(v, 1));
}

TEST_F(SolutionTest, t3) {
    vector<int> v = {1,2,3};
    EXPECT_EQ(2, s.countSubarrays(v, 2));
}

TEST_F(SolutionTest, t4) {
    vector<int> v = {1,9,9,7,4};
    EXPECT_EQ(6, s.countSubarrays(v, 1));
}

TEST_F(SolutionTest, t5) {
    vector<int> v = {1,9,9,7,3,9};
    EXPECT_EQ(14, s.countSubarrays(v, 1));
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
