#include <iostream>
#include <vector>

using namespace std;


class LazySegTree {
public:
    struct Node {
        int left, right, val, tag;
        Node(int l, int r, int v) {left=l; right=r; val=v; tag=0;}
        Node() {left=0; right=0; val=0; tag=0;}
    };

    LazySegTree(vector<int>& v) {
        this->v = v;
        int n = v.size();
        t.resize(4*n);
        build(1, 0, n-1);
    }

    int query(int l, int r) {
        return query(1, l, r);
    }

    void update(int l, int r, int delta) {
        update(1, l, r, delta);
    }

private:
    vector<int> v;
    vector<Node> t;

    void push(int i) {
        t[i*2].val += (t[i*2].right-t[i*2].left+1)*t[i].tag;
        t[i*2+1].val += (t[i*2+1].right-t[i*2+1].left+1)*t[i].tag;
        t[i*2].tag = t[i].tag;
        t[i*2+1].tag = t[i].tag;
        t[i].tag = 0;
    }

    void update(int i, int l, int r, int delta) {
        //cout << "update " << i << ":" << l << "," << r << endl;
        if (t[i].left == l && t[i].right == r) {
            t[i].val += (r-l+1) * delta;
            t[i].tag += delta;
            //cout << "set tag " << i << ":" << t[i].tag << endl;
            return;
        }
        if (r < t[i].left || l > t[i].right) return;
        if (t[i].tag > 0) push(i);
        if (l <= t[i*2].right) update(i*2, l, min(t[i*2].right, r), delta);
        if (r >= t[i*2+1].left) update(i*2+1, max(t[i*2+1].left, l), r, delta);
        t[i].val = t[i*2].val + t[i*2+1].val;
    }

    void build(int i, int l, int r) {
        //cout << "build " << i << ":" << l << "," << r << endl;
        if (l == r) {
            t[i] = Node(l, r, v[l]);
            return;
        }
        int m = (l + r) / 2;
        build(i*2, l, m);
        build(i*2+1, m+1, r);
        t[i] = Node(l, r, t[i*2].val + t[i*2+1].val);
    }

    int query(int i, int l, int r) {
        //cout << "query " << i << ":" << l << "," << r << endl;
        if (t[i].left == l && t[i].right == r) return t[i].val;
        if (r < t[i].left || l > t[i].right) return 0;
        int ans = 0;
        if (l <= t[i*2].right) ans += query(i*2, l, min(r, t[i*2].right));
        if (r >= t[i*2+1].left) ans += query(i*2+1, max(l, t[i*2+1].left), r);
        return ans;
    }
};


int main() {
    vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    LazySegTree t(v);
    cout << "sum of the array is 45:" << t.query(0, 9) << endl;;
    cout << "sum of the 3 to 7 is 25:" << t.query(3, 7) << endl;;
    t.update(3,7,1);
    cout << "after update, sum of the 3 to 7 is 30:" << t.query(3, 7) << endl;;
    t.update(7,8,2);
    cout << "after update, sum of the 3 to 7 is 32:" << t.query(3, 7) << endl;;
    t.update(5,6,3);
    cout << "after update, sum of the 3 to 7 is 38:" << t.query(3, 7) << endl;;
}

