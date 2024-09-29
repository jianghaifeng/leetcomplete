#include <vector>
#include <iostream>

using namespace std;

//also know as Binary Indexed Tree


/*

lowbit: x & (-x)
eg: 5 = 0101
   -5 = 1010 + 1 = 1011
   lowbit = 1
   

         :2    :4    :4    :8    :6    :6    :8    :16
         1,    2,    3,    4,    5,    6,    7,    8
binary: 0001  0010  0011  0100  0101  0110  0111  1000
*/
class BIT {
    vector<int> sum;
public:
    BIT(vector<int>& v) {
        int n = v.size();
        sum.resize(n+1);

        for (int i=0; i<v.size(); i++) update(i+1, v[i]);
    }

    int lowbit(int x) {
        return x & (-x);
    }

    int query(int n) {
        int ans = 0;
        while (n > 0) {
            ans += sum[n];
            n-=lowbit(n);
        }
        return ans;
    }

    void update(int n, int delta) {
        while (n < sum.size()) {
            sum[n]+=delta;
            n+=lowbit(n);
        }
    }

    void debug() {
        for (int i=1; i<sum.size(); i++) cout << sum[i] << ",";
        cout << endl;
    }
};

int main() {
    vector<int> v = {3,2,5,7,3,2,8,9,0,4,6,2};
    BIT bit(v);
    cout << "sum of the first 8 elements: " << bit.query(8) << endl;
    cout << "update the 5st element to 0" << endl;
    bit.update(5, -3);
    cout << "sum of the first 8 elements: " << bit.query(8) << endl;
}
