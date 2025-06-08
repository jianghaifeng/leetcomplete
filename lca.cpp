#include <iostream>
#include <vector>
#include <bit>

using namespace std;

class TreeAncestor {
public:
    vector<vector<int>> pa;

    TreeAncestor(int n, vector<int>& parent) {
        int m = bit_width((unsigned)n);
        pa.resize(n, vector<int>(m, -1));
        for (int i=1; i<n; i++) {
            pa[i][0] = parent[i];
        }

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (int k = pa[j][i]; k != -1) {
                    pa[j][i+1] = pa[k][i];
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        int m = bit_width((unsigned)k);
        for (int i=0; i<m; i++) {
            if ((1<<i)&k) node = pa[node][i];
            if (node<0) break;
        }
        return node;
    }
};

int main() {
    vector<int> parent = {-1,0,0,1,1,2,2};
    TreeAncestor t(7, parent);
    cout << "1=" << t.getKthAncestor(3, 1) << endl;
    cout << "0=" << t.getKthAncestor(5, 2) << endl;
    cout << "-1=" << t.getKthAncestor(6, 3) << endl;
}

