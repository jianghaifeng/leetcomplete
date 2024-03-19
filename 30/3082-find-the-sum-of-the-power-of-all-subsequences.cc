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

    const int mod = 1e9+7;

    long long pow2(int n) {
        if (n == 0) return 1;
        long long tmp = pow2(n/2);
        if (n%2 == 0) return tmp * tmp % mod;
        return tmp * tmp * 2 % mod;
    }

    int sumOfPower(vector<int>& nums, int k) {
        vector<unordered_map<int,long long>> v(k+1);
        v[0][0] = 1;
        for (auto i : nums) {
            for (int j=k-i; j>=0; j--) {
                for (auto [key, val] : v[j]) {
                    v[i+j][key+1] = (v[i+j][key+1] + val) % mod;
                }
            }
        }
        long long ans = 0;
        for (auto [key, val] : v[k]) {
            cout << key << ":" << val << endl;
            ans = (ans + val * pow2(nums.size() - key)) % mod;
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
    vector<int> nums = {1,2,3};
    EXPECT_EQ(6, s.sumOfPower(nums, 3));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {2,3,3};
    EXPECT_EQ(4, s.sumOfPower(nums, 5));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {1,2,3};
    EXPECT_EQ(0, s.sumOfPower(nums, 7));
}

TEST_F(SolutionTest, t4) {
    vector<int> nums = {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1};
    EXPECT_EQ(999634217, s.sumOfPower(nums, 49));
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
