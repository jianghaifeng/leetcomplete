#include <iostream>
#include <vector>
using namespace std;


class MajorityChecker {
public:
    typedef struct TreeNode {
        int start;
        int end;
        int val;
        int weight;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int s, int e, int v, int w) {start=s, end=e, val=v, weight=w, left=nullptr, right=nullptr;}
    } TreeNode;

    vector<int> va;
    TreeNode* root;
    vector<vector<int>> vv;

    MajorityChecker(vector<int>& arr) {
        va = arr;
        root = build(0, arr.size()-1);
        vv = vector<vector<int>>(20001, vector<int>());
        for (int i=0; i<arr.size(); i++) {
            vv[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int threshold) {
        int cand = query(left, right);
        auto itHi = upper_bound(vv[cand].begin(), vv[cand].end(), right);
        auto itLo = lower_bound(vv[cand].begin(), vv[cand].end(), left);
        if (itHi-itLo >= threshold) return cand;
        else return -1;
    }

    int query(int left, int right) {
        return helper(root, left, right).first;
    }

    pair<int, int> helper(TreeNode* t, int l, int r) {
        if (l == t->start && r == t->end) return {t->val, t->weight};

        int m = (t->start+t->end) / 2;
        if (l > m) return helper(t->right, l, r);
        else if (r <= m) return helper(t->left, l, r);
        auto p1 = helper(t->left, l, m);
        auto p2 = helper(t->right, m+1, r);
        if (p1.first == p2.first) return {p1.first, p1.second+p2.second};
        if (p1.second >= p2.second) return {p1.first, p1.second-p2.second};
        else return {p2.first, p2.second-p1.second};
    }

    pair<int,int> merge(const pair<int,int>& p1, const pair<int,int>& p2) {
        if (p1.first == p2.first) return {p1.first, p1.second+p2.second};
        if (p1.second >= p2.second) return {p1.first, p1.second-p2.second};
        else return {p2.first, p2.second-p1.second};
    }
    
    TreeNode* build(int start, int end) {
        if (start == end) return new TreeNode(start, end, va[start], 1);
        int mid = (start + end) / 2;
        TreeNode* l = build(start, mid);
        TreeNode* r = build(mid+1, end);

        auto p = merge({l->val, l->weight}, {r->val, r->weight});
        TreeNode* t = new TreeNode(start, end, p.first, p.second);
        t->left = l;
        t->right = r;
        return t;
    }

    
};

int main() {
    vector<int> v = {1,1,2,2,1,1};
    MajorityChecker mc(v);
    cout << "1=" << mc.query(0,5,4) << endl;
    cout << "-1=" << mc.query(0,3,3) << endl;
    cout << "2=" << mc.query(2,3,2) << endl;
}
