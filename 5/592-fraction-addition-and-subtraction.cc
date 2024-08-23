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
#include <sstream>

using namespace std;

class Solution {
public:

    string tos(pair<int,int>& p) {
        stringstream ss;
        ss << p.first << "/" << p.second;
        return ss.str();
    }

    pair<int,int> add(pair<int,int>& p1, pair<int,int> p2) {
        int g = gcd(p1.second, p2.second);
        int denominator = p1.second / g * p2.second;
        int numerator = p2.second / g * p1.first + p1.second / g * p2.first;
        if (numerator == 0) return {0, 1};
        int g1 = gcd(abs(numerator), denominator);
        return {numerator/g1, denominator/g1};
    }

    pair<int,int> get(string& s, int& pos) {
        string sa = "0", sb = "1";
        auto dv = s.find_first_of('/', pos);
        sa = s.substr(pos, dv-pos);
        pos = dv+1;
        auto op = s.find_first_of("+-", pos);
        if (op == string::npos) {
            sb = s.substr(pos);
            pos = s.length();
        } else {
            sb = s.substr(pos, op-pos);
            pos = op;
        }
        return {stoi(sa), stoi(sb)};
    }

    string fractionAddition(string expression) {
        pair<int,int> ans = {0, 1};
        int pos = 0;
        while (true) {
            auto p = get(expression, pos);
            ans = add(ans, p);
            if (pos == expression.length()) break;
        }
        return tos(ans);
    }

    int gcd(int a, int b) {
        if (a % b == 0) return b;
        return gcd(b, a%b);
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
    EXPECT_EQ("0/1", s.fractionAddition("-1/2+1/2"));
}

TEST_F(SolutionTest, t2) {
    EXPECT_EQ("1/3", s.fractionAddition("-1/2+1/2+1/3"));
}

TEST_F(SolutionTest, t3) {
    EXPECT_EQ("-1/6", s.fractionAddition("1/3-1/2"));
}

TEST_F(SolutionTest, t4) {
}

TEST_F(SolutionTest, t5) {
}


int main() {
    InitGoogleTest();
    return RUN_ALL_TESTS();
}
