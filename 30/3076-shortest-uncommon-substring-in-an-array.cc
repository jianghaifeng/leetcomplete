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
    struct Trie {
        unordered_set<int> s;
        Trie* next[26];
        void insert(int i) {s.insert(i);}
        bool only(int i) {return s.size() == 1 && s.count(i) > 0;}
        bool contains(int i) {return s.count(i) > 0;}
        Trie(int i) {s.insert(i); for(int i=0; i<26; i++) next[i]=nullptr;}
    };

    void add(Trie* node, vector<string>& arr, int i, int start) {
        while (start < arr[i].length()) {
            int n = arr[i][start] - 'a';
            if (node->next[n] == nullptr) {
                node->next[n] = new Trie(i);
            } else {
                node->next[n]->insert(i);
            }
            node = node->next[n];
            start++;
        }
    }

    void query(Trie* node, vector<string>& arr, int i, int start, string& res) {
        for (int j=start; j<arr[i].length(); j++) {
            int n = arr[i][j] - 'a';
            if (node->next[n]->only(i)) {
                string tmp = arr[i].substr(start, j-start+1);
                if (tmp.length() < res.length()) res = tmp;
                else if (tmp.length() == res.length()) res = min(res, tmp);
                break;
            }
            node = node->next[n];
        }
    }

    vector<string> shortestSubstrings(vector<string>& arr) {
        Trie* root = new Trie(-1);

        for (int i=0; i<arr.size(); i++) {
            for (int j=0; j<arr[i].length(); j++)
                add(root, arr, i, j);
        }

        string maxs(21, 'z');
        vector<string> ans;
        for (int i=0; i<arr.size(); i++) {
            string res = maxs;
            for (int j=0; j<arr[i].length(); j++)
                query(root, arr, i, j, res);
            if (res == maxs) ans.push_back("");
            else ans.push_back(res);
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
    vector<string> arr = {"cab","ad","bad","c"};
    EXPECT_THAT(s.shortestSubstrings(arr), ElementsAre("ab","","ba",""));
}

TEST_F(SolutionTest, t2) {
    vector<string> arr = {"abc","bcd","abcd"};
    EXPECT_THAT(s.shortestSubstrings(arr), ElementsAre("","","abcd"));
}

TEST_F(SolutionTest, t3) {
    vector<string> arr = {"gfnt","xn","mdz","yfmr","fi","wwncn","hkdy"};
    EXPECT_THAT(s.shortestSubstrings(arr), ElementsAre("g","x","z","r","i","c","h"));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
