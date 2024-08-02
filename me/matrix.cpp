#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> multiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    assert(a[0].size() == b.size());
    int m = a.size();
    int n = a[0].size();
    int p = b[0].size();
    // Dimension of the matrix should be valid
    // Result matrix initialized with 0s
    vector<vector<int>> res(m, vector<int>(p, 0));
    // Perform multiplication
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

vector<vector<int>> pow(const vector<vector<int>>& a, int k) {
    int n = a.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    // Initialize result matrix as identity matrix
    for (int i = 0; i < n; i++) res[i][i] = 1;
    vector<vector<int>> base = a;
    while (k > 0) {
        if (k % 2 == 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        k /= 2;
    }
    return res;
}
