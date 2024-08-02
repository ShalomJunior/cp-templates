#include <bits/stdc++.h>
using namespace std;

struct mex_tracker {
    int n;
    vector<int> freq;
    bitset<5001> s;
    mex_tracker(int _n) : n(_n) {
        freq.resize(n + 1);
        s.set();
    }

    void add(int x) {
        if (!freq[x]++) s[x] = 0;
    }

    void sub(int x) {
        if (!--freq[x]) s[x] = 1;
    }

    int query() {
        return s._Find_first();
    }
};