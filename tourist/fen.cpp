#include <bits/stdc++.h>
using namespace std;

template <typename T>
class fenwick {
public:
    vector<T> fenw;
    int n;

    fenwick(int _n) : n(_n) {
        fenw.resize(n);
    }

    void modify(int x, T v) {
        while (x < n) {
            fenw[x] += v;
            x |= (x + 1);
        }
    }

    T get(int x) {
        T v{};
        while (x >= 0) {
            v += fenw[x];
            x = (x & (x + 1)) - 1;
        }
        return v;
    }
};

struct node {
    int a = 0; // don't forget to set default value

    inline void operator += (node& other) {
    }
};