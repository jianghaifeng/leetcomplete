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

    int lowbit(int n) {
        return n & (-n);
    }

    void update(vector<int>& arr, int n) {
        while (n < arr.size()) {
            arr[n]++;
            n += lowbit(n);
        }
    }

    int query(vector<int>& arr, int n) {
        int ans = 0;
        while (n > 0) {
            ans += arr[n];
            n -= lowbit(n);
        }
        return ans;
    }

    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int,int>> vp;
        
        for (int i=0; i<n; i++) vp.push_back({nums[i], i});
        auto comp = [](pair<int,int>& p1, pair<int,int>& p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first < p2.first;
        };
        sort(vp.begin(), vp.end(), comp);

        for (int i=0; i<vp.size(); i++) nums[vp[i].second] = i+1;
        for (auto i : nums) cout << i << ","; cout << endl;

        vector<int> arr1(n+1), arr2(n+1);
        update(arr1, nums[0]);
        update(arr2, nums[1]);
        vector<int> v1 = {vp[nums[0]-1].first}, v2 = {vp[nums[1]-1].first};

        for (int i=2; i<n; i++) {
            int cnt1 = v1.size() - query(arr1, nums[i]);
            int cnt2 = v2.size() - query(arr2, nums[i]);
            if (cnt1 > cnt2 || (cnt1 == cnt2 && v1.size() <= v2.size())) {
                v1.push_back(vp[nums[i]-1].first);
                update(arr1, nums[i]);
            } else {
                v2.push_back(vp[nums[i]-1].first);
                update(arr2, nums[i]);
            }
        }

        for (auto i : v2) v1.push_back(i);
        return v1;
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
    vector<int> nums = {2,1,3,3};
    EXPECT_THAT(s.resultArray(nums), ElementsAre(2,3,1,3));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {5,14,3,1,2};
    EXPECT_THAT(s.resultArray(nums), ElementsAre(5,3,1,2,14));
}

TEST_F(SolutionTest, t3) {
    vector<int> nums = {3,3,3,3};
    EXPECT_THAT(s.resultArray(nums), ElementsAre(3,3,3,3));
}

int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
