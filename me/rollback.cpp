#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
    vector<int> parents;
    vector<int> sizes;
    stack<tuple<int, int, int>> history; // Stack to store changes

    dsu(int n) {
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        sizes.resize(n, 1);
    }

    int root(int u) {
        return parents[u] == u ? u : parents[u] = root(parents[u]);
    }

    bool join(int u, int v) {
        int a = root(u);
        int b = root(v);
        if (a == b) return false;
        if (sizes[a] > sizes[b]) swap(a, b);
        // Record the changes for rollback
        history.push({ a, parents[a], sizes[b] });
        parents[a] = b;
        sizes[b] += sizes[a];
        return true;
    }

    bool rollback() {
        if (history.empty()) return false;
        auto [a, oldParent, oldSize] = history.top();
        history.pop();
        sizes[parents[a]] = oldSize;
        parents[a] = oldParent;
        return true;
    }
};