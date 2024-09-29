#include <iostream>
#include <vector>

using namespace std;
class SegmentTree {
public:
    struct Node {
        int val, start, end;
        Node* left;
        Node* right;
        Node(int v, int s, int e) {val=v; start=s; end=e; right=left=nullptr;}
        Node(int v, int s, int e, Node* l, Node* r) {val=v; start=s; end=e; left=l; right=r;}
    };

    Node* root;

    SegmentTree(vector<int>& v) {
        root = build(v, 0, v.size()-1);
    }

    Node* build(vector<int>& v, int l, int r) {
        if (l == r) return new Node(v[l], l, r);
        int m = (l+r) / 2;
        Node* left = build(v, l, m);
        Node* right = build(v, m+1, r);
        return new Node(left->val+right->val, l, r, left, right);
    }

    int query(int start, int end, Node* node) {
        int ans = 0;
        if (start == node->start && end == node->end) return node->val;
        if (node->left && node->left->end >= start) 
            ans += query(start, min(node->left->end, end), node->left);
        if (node->right && node->right->start <= end)
            ans += query(max(start, node->right->start), end, node->right);
        return ans;
    }

    int querySum(int start, int end) {
        return query(start, end, root);
    }

    void update(int start, int end, int newval, Node* node) {
        if (start == node->start && end == node->end && start == end) {node->val = newval; return;}
        if (node->left && node->left->end >= start)
            update(start, min(node->left->end, end), newval, node->left);
        if (node->right && node->right->start <= end) 
            update(max(start, node->right->start), end, newval, node->right);
        node->val = 0;
        if (node->left) node->val += node->left->val;
        if (node->right) node->val += node->right->val;
    }

    void update(int start, int end, int newval) {
        update(start, end, newval, root);
    }

    void print(Node* node, int indent) {
        string prefix(2*indent, ' ');
        cout << prefix << "(" << node->start << "," << node->end << ":" << node->val << ")" << endl;
        if (node->left) print(node->left, indent+1);
        if (node->right) print(node->right, indent+1);
    }

    void printTree() {
        print(root, 0);
    }
};

void output(vector<int>& v) {
    for (auto i : v) cout << i << ","; cout << endl;
}

int main() {
    vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    SegmentTree tree(v);
    cout << "all elements:" << endl;
    output(v);
    cout << "sum for all should be 55:" << tree.querySum(0, 10) << endl;
    tree.printTree();
    cout << "sum for index range 2 and 6 should be 20:" << tree.querySum(2, 6) << endl;
    cout << "sum for index range 4 and 8 should be 30:" << tree.querySum(4, 8) << endl;
    cout << "update index rang 0 and 6 to 0" << endl;
    tree.update(0,6,0);
    tree.printTree();
    cout << "sum for index range 2 and 7 should be 7:" << tree.querySum(2, 7) << endl;
    cout << "sum for index range 0 and 8 should be 15:" << tree.querySum(0, 8) << endl;
}
