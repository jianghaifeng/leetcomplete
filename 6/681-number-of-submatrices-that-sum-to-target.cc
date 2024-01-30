class Solution {
public:
    int helper(vector<vector<int>>& preSums, int l, int r, int target) {
        int sum = 0, ans = 0;
        unordered_map<int,int> m; m[0] = 1;
        for (int i=0; i<preSums.size(); i++) {
            sum += preSums[i][r+1] - preSums[i][l];
            ans += m[sum-target];
            m[sum]++;
        }
        return ans;
    }

    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int w = matrix[0].size(), h = matrix.size();
        vector<vector<int>> preSums;
        for (int i=0; i<h; i++) {
            vector<int> v = {0};
            for (int j=0; j<w; j++) v.push_back(v.back() + matrix[i][j]);
            preSums.push_back(v);
        }
        int ans = 0;
        for (int i=0; i<w; i++) {
            for (int j=i; j<w; j++) {
                ans += helper(preSums, i, j, target);
            }
        }
        return ans;
    }
};
