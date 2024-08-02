#include< bits/stdc++.h>
using namespace std;

class segtree {
    struct node {
        int val;
        node() : val(0) {}
    }
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }
    int n;
    vector<node> tree;
    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
    }
    void update(int pos, int val) {
        update(0, 0, n - 1, pos, val);
    }
    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[v].val = val;
            return
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(2 * v + 1, tl, tm, pos, val);
        }
        else {
            update(2 * v + 2, tm + 1, tr, pos, val);
        }
        tree[v] = unite(tree[2 * v + 1], tree[2 * v + 2]);
    }
    node query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return node();
        int tm = (tl + tr) / 2;
        node left = query(2 * n + 1, tl, tm, l, min(tm, r));
        node right = query(2 * n + 2, tm + 1, tr, max(l, tm + 1), r);
        return unite(left, right);
    }
};