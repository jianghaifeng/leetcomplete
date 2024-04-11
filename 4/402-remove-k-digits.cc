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


    string removeKdigits(string num, int k) {
        string tmp;
        int top = 0;
        for (int i=0; i<k; i++) {
            while (tmp.length() > top && tmp.back() > num[i]) tmp.pop_back();
            tmp.push_back(num[i]);
        }
        for (int i=k; i<num.length(); i++) {
            while (tmp.length() > top && tmp.back() > num[i]) tmp.pop_back();
            tmp.push_back(num[i]);
            top++;
        }
        int start = 0;
        while (start < top && tmp[start] == '0') start++;
        if (start == top) return "0";
        return tmp.substr(start, top-start);
    }

    using PII = pair<char,int>;
    string removeKdigits1(string num, int k) {
        if (num.length() == k) return "0";

        auto comp=[](PII& p1, PII& p2) {
            if (p1.first == p2.first) {
                return p1.second < p2.second;
            }
            return p1.first > p2.first;
        };
        priority_queue<PII, vector<PII>, decltype(comp)> pq(comp);

        string ans;
        int lastPos = -1;
        for (int i=0; i<k; i++) pq.push({num[i], i});
        for (int i=k; i<num.length(); i++) {
            pq.push({num[i], i});
            while (pq.top().second <= lastPos) pq.pop();
            lastPos = pq.top().second;
            if (ans.length() > 0 || pq.top().first != '0') ans.push_back(pq.top().first);
            pq.pop();
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
    EXPECT_EQ("1219", s.removeKdigits("1432219", 3));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ("200", s.removeKdigits("10200", 1));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ("0", s.removeKdigits("10", 2));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {

    InitGoogleTest();
    return RUN_ALL_TESTS();
}
