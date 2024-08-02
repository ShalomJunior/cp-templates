#include <bits/stdc++.h>
using namespace std;

struct tree {
    vector<int> val;
    int n;
    tree(int _n) {
        n = _n;
        val.resize(4 * n);
        init(1, 0, n - 1);
    }

    void init(int v, int tl, int tr) {
        if (tl == tr) {
            val[v] = tl;
            return;
        }
        int tm = (tl + tr) / 2;
        init(2 * v, tl, tm);
        init(2 * v + 1, tm + 1, tr);
    }

    void push(int v) {
        for (int u : {2 * v, 2 * v + 1}) {
            val[u] = max(val[u], val[v]);
        }
    }

    void set_seg(int v, int tl, int tr, int l, int r, int x) {
        if (r < tl || l > tr) return;
        if (l <= tl && tr <= r) {
            val[v] = max(val[v], x);
            return;
        }
        int tm = (tl + tr) / 2;
        push(v);
        set_seg(2 * v, tl, tm, l, r, x);
        set_seg(2 * v + 1, tm + 1, tr, l, r, x);
    }

    void set_seg(int l, int r, int x) {
        set_seg(1, 0, n - 1, l, r, x);
    }

    int query(int v, int tl, int tr, int i) {
        if (tl == tr) return val[v];
        push(v);
        int tm = (tl + tr) / 2;
        if (i <= tm) return query(2 * v, tl, tm, i);
        else return query(2 * v + 1, tm + 1, tr, i);
    }

    int query(int i) {
        return query(1, 0, n - 1, i);
    }
};