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


    string frequencySort(string s) {
        vector<pair<int,int>> freq(128, {0,0});
        for (auto c : s) freq[c].first++;
        for (int i=0; i<128; i++) freq[i].second = i;
        auto comp = [](pair<int,int>& p1, pair<int,int>& p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first > p2.first;
        };
        sort(freq.begin(), freq.end(), comp);
        string ans;
        for (auto [f, c] : freq) {
            if (f == 0) break;
            ans += string(f, c);
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
    EXPECT_EQ("eert", s.frequencySort("tree"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ("aaaccc", s.frequencySort("cccaaa"));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ("bbAa", s.frequencySort("Aabb"));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
