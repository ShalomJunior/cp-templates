#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int p[N];

struct node {
    int l, r, cnt;
    node* left, * right;
    node(int _l, int _r) : l(_l), r(_r), left(nullptr), right(nullptr), cnt(0) {};

    void modify(int x, int d) {
        cnt += d;
        if (l == r) return;
        int m = (l + r) / 2;
        if (x <= m) {
            if (left == nullptr) left = new node(l, m);
            left->modify(x, d);
        }
        else {
            if (right == nullptr) right = new node(m + 1, r);
            right->modify(x, d);
        }
    }

    int query(int lo, int hi) {
        if (lo > r || hi < l) return 0;
        if (lo <= l && r <= hi) return cnt;
        int m = (l + r) / 2;
        if (left == nullptr) left = new node(l, m);
        if (right == nullptr) right = new node(m + 1, r);
        return left->query(lo, hi) + right->query(lo, hi);
    }
};

struct segtree {
    node* t[4 * N];
    int n;
    segtree(int _n) : n(_n) {
        init(1, 1, n);
    }

    void init(int v, int tl, int tr) {
        t[v] = new node(1, n);
        for (int i = tl; i <= tr; i++) t[v]->modify(p[i], 1);
        if (tl == tr) return;
        int tm = (tl + tr) / 2;
        init(2 * v, tl, tm);
        init(2 * v + 1, tm + 1, tr);
    }

    int query(int v, int tl, int tr, int l, int r, int lo, int hi) {
        if (l > tr || r < tl) return 0;
        if (l <= tl && tr <= r) return t[v]->query(lo, hi);
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, r, lo, hi) + query(2 * v + 1, tm + 1, tr, l, r, lo, hi);
    }

    int query(int l, int r, int lo, int hi) {
        return query(1, 1, n, l, r, lo, hi);
    }

    void modify(int v, int tl, int tr, int i, int x, int d) {
        t[v]->modify(x, d);
        if (tl == tr) return;
        int tm = (tl + tr) / 2;
        if (i <= tm) modify(2 * v, tl, tm, i, x, d);
        else modify(2 * v + 1, tm + 1, tr, i, x, d);
    }

    void modify(int i, int x, int d) {
        modify(1, 1, n, i, x, d);
    }
};