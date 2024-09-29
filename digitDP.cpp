#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//Find count of numbers in range [L, R] such that sum of its digits is a prime number.

bool isPrime(int n) {
    if (n < 2) return false;
    int i = 2;
    while (i <= sqrt(n)) {
        if (n % i == 0) return false;
        i++;
    }
    return true;
}

int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n%10;
        n /= 10;
    }
    return sum;
}

int bruteForce(string& sn) {
    int ans = 0;
    int n = stoi(sn);
    for (int i=0; i<=n; i++) {
        if (isPrime(digitSum(i))) ans++;
    }
    return ans;
}

int calc(string& s) {
    vector<vector<int>> dp(20, vector<int>(200));
    int n = s.length();
    dp[0][0] = 1;
    for (int i=0; i<=n-2; i++) {
        for (int k=0; k<=9; k++) {
            for (int j=0; j+k<200; j++) {
                if (dp[i][j] != 0) {
                }
                dp[i+1][j+k] += dp[i][j];
            }
        }
    }
    int ans = 0;
    for (int i=1; i<=9; i++) {
        for (int j=0; i+j<200; j++) {
            int sum = 0;
            for (int k=0; k<=n-2; k++) {
                sum += dp[k][j];
            }
            if (isPrime(i+j)) {
                ans += sum;
            }
        }
    }
    int total = 0;
    for (int i=0; i<n; i++) {
        if (i == 0) {
            for (int k=1; k<s[i]-'0'; k++) {
                for (int j=0; j<200-total-k; j++) {
                    dp[n][j+total+k] += dp[n-i-1][j];
                }
            }
        } else {
            for (int k=0; k<s[i]-'0'; k++) {
                for (int j=0; j<200-total-k; j++) {
                    dp[n][j+total+k] += dp[n-i-1][j];
                }
            }
        }
        total += s[i] - '0';
    }
    dp[n][total] += 1;
    for (int t=0; t<200; t++) {
        if (isPrime(t)) ans += dp[n][t];
    }
    return ans;
}

int digit_dp(string ss) {
    int n = ss.size();
    vector<vector<vector<int>>> dp(20, vector<vector<int>>(2, vector<int>(200)));

    //empty suffixes having sum=0
    dp[n][0][0] = 1;
    dp[n][1][0] = 1;

    for(int i = n-1; i >=0 ; i--) {
        for(int tight = 0; tight < 2 ; tight++) {
            for(int sum = 0; sum < 200 ; sum++) {
                if(tight) {
                    for(int d = 0; d <= ss[i] - '0' ; d++) {
                        dp[i][1][sum] += (d == ss[i]-'0') ? dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
                    }
                }
                else {
                    for(int d = 0; d < 10 ; d++) {
                        dp[i][0][sum] += dp[i+1][0][sum-d];
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < 200; i++) {
        if(isPrime(i)) ans += dp[0][1][i];
    }
    return ans;
}

int main() {
    string sn = "2386";
    cout <<"calc:" << calc(sn) << endl;
    cout <<"bruteForce:" << bruteForce(sn) << endl;
    cout <<"digitDp:" << digit_dp(sn) << endl;
    sn = "8296398745639";
    cout << digit_dp(sn) << endl;
    return 0;
}
