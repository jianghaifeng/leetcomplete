#include <iostream>
#include <string>
#include <vector>
#include <chrono> 

using namespace std;
using namespace std::chrono;

class Solution {
public:
    vector<int> calcNext(const string& sub) {
        vector<int> next(sub.length());
        for (int i=1, j=0; i<sub.length(); i++) {
            while (j > 0 && sub[j] != sub[i]) j = next[j-1];
            if (sub[i] == sub[j]) j++;
            next[i] = j;
        }
        return next;
    }

    int findIndex(const string& s, const string& sub) {
        vector<int> next = calcNext(sub);
        for (int i=0, j=0; i<s.length(); i++) {
            while (j > 0 && s[i] != sub[j]) j = next[j-1];
            if (s[i] == sub[j]) j++;
            if (j == sub.length()) return i-j+1;
        }
        //for (auto i : next) cout << i << ","; cout << endl;
        return -1;
    }

    int bruteForce(const string& s, const string& sub) {
        int i = 0, j = 0;
        while (i < s.length()) {
            int k = i;
            while (k < s.length() && j < sub.length() && s[k] == sub[j]) k++, j++;
            if (j == sub.length()) return i;
            if (k == s.length()) return -1;
            i++; j=0;
        }
        return -1;
    }
};

int main() {
    Solution s;
    string full = "ababababaababababaaabbbbababacccabaabababaabbababbabbbabbabababcbabcd";
    //string sub = "abababaabbababbabbbabbabababc";
    string sub = "abababaabbababbabbbabbababaibc";

    auto start = high_resolution_clock::now();
    int res = s.findIndex(full, sub); 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "KMP time:" << duration.count() << ", result=" << res << endl;

    start = high_resolution_clock::now();
    res = s.bruteForce(full, sub);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "brute force time:" << duration.count() << ", result=" << res << endl;

    start = high_resolution_clock::now();
    res = full.find(sub);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "string.find time:" << duration.count() << ", result=" << res << endl;
}
