#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

const int root = 31; // primitive (2^k)th root
const int root_1 = inversemod(root, MOD);
const int root_pw = 1 << 23;




int inversemod(int p, int q) {
    // assumes p > 0
    // https://codeforces.com/blog/entry/23365
    return (p > 1 ? q - 1LL * inversemod(q % p, p) * q / p : 1);
}

// source: cp-algorithms
void fft(vector<int>& a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1) wlen = (int)(1LL * wlen * wlen % MOD);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % MOD);
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                w = (int)(1LL * w * wlen % MOD);
            }
        }
    }

    if (invert) {
        int n_1 = inversemod(n, MOD);
        for (int& x : a) x = (int)(1LL * x * n_1 % MOD);
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] = 1LL * fa[i] * fb[i] % MOD;
    fft(fa, true);
    fa.resize(a.size() + b.size() - 1);
    return fa;
}