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


    struct Trie {
        Trie* next[10];
        Trie() {for (int i=0; i<10; i++) next[i]=nullptr;}
    };

    Trie *root;

    void add(int n) {
        string sn = to_string(n);
        Trie* p = root;
        for (auto c : sn) {
            int index = c - '0';
            if (p->next[index] == nullptr) {
                p->next[index] = new Trie();
            }
            p = p->next[index];
        }
    }

    int query(int n) {
        string sn = to_string(n);
        Trie* p = root;
        int ans = 0;
        for (auto c : sn) {
            int index = c - '0';
            if (p->next[index]) p = p->next[index], ans++;
            else break;
        }
        return ans;
    }

    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        root = new Trie();
        for (auto i : arr1) add(i);
        int ans = 0;
        for (auto i : arr2) ans = max(ans, query(i));
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
    vector<int> arr1 = {1,10,100};
    vector<int> arr2 = {1000};
    EXPECT_EQ(3, s.longestCommonPrefix(arr1, arr2));
}

TEST_F(SolutionTest, t2) {
    vector<int> arr1 = {1,2,3};
    vector<int> arr2 = {4,4,4};
    EXPECT_EQ(0, s.longestCommonPrefix(arr1, arr2));
}



int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
