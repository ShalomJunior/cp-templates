#include <bits/stdc++.h>
using namespace std;

class segtree {
public:
    struct node {
        int val = 0;
    };

    node unite(const node& a, const node& b) const {
        node res;
        // Combine values of nodes 'a' and 'b' as needed for your specific problem
        res.val = a.val + b.val; // Example: sum of values
        return res;
    }

    int n;
    vector<node> tree;

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            // Leaf node, initialize with appropriate values
            // For example, read the input array values and store in the leaf nodes
            // tree[v].val = input[tl];
        }
        else {
            int tm = (tl + tr) / 2;
            build(2 * v + 1, tl, tm);
            build(2 * v + 2, tm + 1, tr);
            tree[v] = unite(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    void update(int pos, int val) {
        update(0, 0, n - 1, pos, val);
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            // Leaf node, update the value
            tree[v].val = val;
        }
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(2 * v + 1, tl, tm, pos, val);
            }
            else {
                update(2 * v + 2, tm + 1, tr, pos, val);
            }
            tree[v] = unite(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    node query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            // Return an identity element for your specific operation (e.g., 0 for sum)
            return node();
        }
        if (tl == l && tr == r) {
            // Range matches exactly with the current segment
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        node left = query(2 * v + 1, tl, tm, l, min(r, tm));
        node right = query(2 * v + 2, tm + 1, tr, max(l, tm + 1), r);
        return unite(left, right);
    }
};
