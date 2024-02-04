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


    struct Counter {
        multiset<int> lo;
        unordered_map<char, int> chPos;
        unordered_map<char, queue<int>> chQueue;
        unordered_map<char, int> chLen;
        int minPos = -1;

        Counter(string& t) {
            for (auto c : t) chLen[c]++;
            for (auto [c, l] : chLen) {
                chPos[c] = -1;
                lo.insert(-1);
                chQueue[c] = queue<int>();
            }
        }

        void debug() {
            cout << "lo:";
            for (auto i : lo) cout << i << ","; cout << endl;
            cout << "chPos:";
            for (auto [c, p] : chPos) cout << c << "," << p << " "; cout << endl;
        }

        void insert(char c, int pos) {
            if (chLen.count(c) == 0) return;
            chQueue[c].push(pos);
            while (chQueue[c].size() > chLen[c]) chQueue[c].pop();
            if (chQueue[c].size() == chLen[c]) {
                lo.erase(lo.find(chPos[c]));
                chPos[c] = chQueue[c].front();
                lo.insert(chPos[c]);
                minPos = *lo.begin();
            }
        }

        int getMinPos() {
            return minPos;
        }
    };

    string minWindow1(string s, string t) {

        Counter cntr(t);

        string ans = "";
        int last = -1;

        for (int i=0; i<s.length(); i++) {
            cntr.insert(s[i], i);
            if (cntr.getMinPos() != last) {
                last = cntr.getMinPos();
                if (ans.empty() || i-last+1 < ans.length())
                    ans = s.substr(last, i-last+1);
            }
        }
        return ans;
    }


    string minWindow(string s, string t) {
        vector<int> v(127);
        for (auto c : t) v[c]++;

        int start=-1, len=s.length()+1, count=t.length();

        for (int i=0, j=0; i<s.length() && j<s.length(); i++) {
            while (j < s.length() && count > 0) {
                if (v[s[j]] > 0) count--;
                v[s[j]]--;
                j++;
            }
            while (i < s.length() && v[s[i]] < 0) v[s[i]]++, i++;
            if (count == 0 && j-i < len) start=i, len=j-i;
            v[s[i]]++, count++;
        }
        if (start >= 0) return s.substr(start, len);
        return "";
    }


};

/*

ADOBECODEBANC
i
      j

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
    EXPECT_EQ("BANC", s.minWindow("ADOBECODEBANC", "ABC"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ("a", s.minWindow("a", "a"));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ("", s.minWindow("a", "aa"));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
