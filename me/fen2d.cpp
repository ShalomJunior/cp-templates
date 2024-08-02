#include<bits/stdc++.h>
using namespace std;

template<typename T>
class fenwick {
public:
    fenwick(int n, int m) {
        this->n = n;
        this->m = m;
        // Resize the tree to n+3 and m+3 for convenient bitwise operations
        tree.resize(n + 3, vector<T>(m + 3, 0));
    }

    void update(int x, int y, T val) {
        // Iterate through x and y dimensions using bitwise operations
        for (int i = x; i <= n; i += (i & -i)) {
            for (int j = y; j <= m; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    T query(int x, int y) {
        T sum = 0;
        // Similar to 1D Fenwick tree, iterate using bitwise operations
        for (int i = x; i > 0; i -= (i & -i)) {
            for (int j = y; j > 0; j -= (j & -j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // Range query using four quadrant sums for efficient calculation
    T rangeQuery(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }

private:
    int n, m;
    // 2D tree to store prefix sums
    vector<vector<T>> tree;
};
