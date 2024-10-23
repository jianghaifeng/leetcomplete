#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <vector>

using namespace std;


class Solution {
public:

    string longestPalindrome(string s) {
        string sn = "^#";
        for (auto c : s) sn.push_back(c), sn.push_back('#');
        sn.push_back('$');
        vector<int> v(sn.length());
        int c = 0, r = 0;
        for (int i=2; i<sn.length(); i++) {
            if (i <= r) v[i] = min(r-i, v[2*c - i]);
            while (sn[i-v[i]-1] == sn[i+v[i]+1]) v[i]++;
            if (i+v[i] > r) r = v[i], c = i;
        }
        int maxCenter = max_element(v.begin(), v.end()) - v.begin();
        int maxLen = v[maxCenter];
        return s.substr(((maxCenter-1)/2 - maxLen/2), maxLen);
    }

    string longestPalindrome_orig(string s) {
        int maxLen=1, maxPos=0;
        vector<int> v = {1};
        for (int i=1; i<s.length(); i++) {
            vector<int> tmp = {1};
            if (s[i] == s[i-1]) tmp.push_back(2);
            for (auto len : v) {
                if (i-len-1 >= 0 && s[i] == s[i-len-1]) {
                    tmp.push_back(len+2);
                }
            }
            if (tmp.back() > maxLen) maxLen = tmp.back(), maxPos = i - maxLen + 1;
            swap(tmp, v);
        }
        return s.substr(maxPos, maxLen);
    }

};

class SolutionFixture : public ::testing::Test {
public:
    virtual void setUp() {}
    virtual void tearDown() {}
    
    Solution s;
};


TEST_F(SolutionFixture, t1) {
    EXPECT_EQ("bab", s.longestPalindrome("babad"));
}

TEST_F(SolutionFixture, t2) {
    EXPECT_EQ("bb", s.longestPalindrome("cbbd"));
}

TEST_F(SolutionFixture, t3) {
    EXPECT_EQ("a", s.longestPalindrome("a"));
}

TEST_F(SolutionFixture, t4) {
    EXPECT_EQ("aca", s.longestPalindrome("aacabdkacaa"));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
