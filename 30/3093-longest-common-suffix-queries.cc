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

    struct Trie {
        Trie* next[26];
        int id;
        Trie(int id) {
            this->id = id;
            for(int i=0; i<26; i++) next[i]=nullptr;
        }
    };

    void add(vector<string>& v, int i, Trie* root) {
        if (v[i].length() < v[root->id].length()) root->id = i;
        Trie* p = root;
        for (int k=v[i].length()-1; k>=0; k--) {
            int n = v[i][k] - 'a';
            if (p->next[n] == nullptr) p->next[n] = new Trie(i);
            else {
                if (v[i].length() < v[p->next[n]->id].length()) p->next[n]->id = i;
            }
            p = p->next[n];
        }
    }

    int query(Trie* root, string& s) {
        Trie* p = root;
        for (int i=s.length()-1; i>=0; i--) {
            int n = s[i]-'a';
            if (p->next[n] == nullptr) break;
            p = p->next[n];
        }
        return p->id;
    }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie* root = new Trie(0);
        for (int i=0; i<wordsContainer.size(); i++) add(wordsContainer, i, root);
        vector<int> ans;
        for (auto& s : wordsQuery) {
            ans.push_back(query(root, s));
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
    vector<string> c = {"abcd","bcd","xbcd"};
    vector<string> q = {"cd","bcd","xyz"};
    EXPECT_THAT(s.stringIndices(c, q), ElementsAre(1,1,1));
}

TEST_F(SolutionTest, t2) {
    vector<string> c = {"abcdefgh","poiuygh","ghghgh"};
    vector<string> q = {"gh","acbfgh","acbfegh"};
    EXPECT_THAT(s.stringIndices(c, q), ElementsAre(2,0,2));
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
