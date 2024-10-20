#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int pos;
    string s;
    bool parseBoolExpr(string expression) {
        s = expression;
        pos = 0;
        return parse();
    }

    bool parse() {
        if (s[pos] == '&') return parseAnd();
        if (s[pos] == '|') return parseOr();
        if (s[pos] == '!') return parseNot();
        return parseSingle();
    }

    bool parseSingle() {
        // cout << "single:" << pos << endl;
        bool res = (s[pos] == 't');
        pos++;
        return res;
    }

    bool parseNot() {
        // cout << "not:" << pos << endl;
        pos += 2;
        bool res = parse();
        pos++;
        return !res;
    }

    bool parseAnd() {
        // cout << "and:" << pos << endl;
        pos++;
        bool res = true;
        do {
            pos++;
            res = parse() && res;
            // cout << pos << ":" << s[pos] << endl;
        } while (s[pos] == ',');
        pos++;
        return res;
    }

    bool parseOr() {
        // cout << "or:" << pos << endl;
        pos++;
        bool res = false;
        do {
            pos++;
            res = parse() || res;
            // cout << pos << ":" << s[pos] << endl;
        } while (s[pos] == ',');
        pos++;
        return res;
    }
};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    EXPECT_EQ(false, s.parseBoolExpr("&(|(f))"));
}

TEST_F(SolutionFixture, t2) {
    EXPECT_EQ(true, s.parseBoolExpr("|(f,f,f,t)"));
}

TEST_F(SolutionFixture, t3) {
    EXPECT_EQ(true, s.parseBoolExpr("!(&(f,t))"));
}

TEST_F(SolutionFixture, t4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
