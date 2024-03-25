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

    using LL = long long;
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        auto comp = [](pair<int,LL>& p1, pair<int,LL>& p2) {
            return p1.second < p2.second;
        };
        vector<LL> v(100001), ans;

        priority_queue<pair<int,LL>, vector<pair<int,LL>>, decltype(comp)> pq(comp);
        for (int i=0; i<nums.size(); i++) {
            v[nums[i]] += freq[i];
            pq.push({nums[i], v[nums[i]]});
            while (true) {
                auto p = pq.top();
                if (v[p.first] == p.second) break;
                else pq.pop();
            }
            
            if (pq.empty()) ans.push_back(0);
            else ans.push_back(pq.top().second);
        }
        return ans;
    }

};


/*


3, 2:3
2, 2:3, 3:2
-3, 
1
 
2:3, 1:1
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
    vector<int> nums = {2,3,2,1};
    vector<int> freq = {3,2,-3,1};
    EXPECT_THAT(s.mostFrequentIDs(nums,freq), ElementsAre(3,3,2,2));
}

TEST_F(SolutionTest, t2) {
    vector<int> nums = {5,5,3};
    vector<int> freq = {2,-2,1};
    EXPECT_THAT(s.mostFrequentIDs(nums,freq), ElementsAre(2,0,1));
}

TEST_F(SolutionTest, t3) {
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
