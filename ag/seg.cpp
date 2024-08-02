#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int N = 3e5 + 5;

struct tree {
    int cnt[4 * N];
    long long tot[4 * N];
    void init(int v, int tl, int tr) {
        cnt[v] = 0;
        tot[v] = 0;
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            init(2 * v, tl, tm);
            init(2 * v + 1, tm + 1, tr);
        }
    }

    void modify(int v, int tl, int tr, int i, int x, int d) {
        cnt[v] += d;
        tot[v] += d * x;
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            if (i <= tm) modify(2 * v, tl, tm, i, x, d);
            else modify(2 * v + 1, tm + 1, tr, i, x, d);
        }
    }

    long long query(int v, int k) {
        if (k == 0) return 0;
        if (cnt[v] < k) return INF;
        if (cnt[v] == k) return tot[v];
        if (cnt[2 * v] >= k) return query(2 * v, k);
        else return tot[2 * v] + query(2 * v + 1, k - cnt[2 * v]);
    }
} Tree[2];