#include<bits/stdc++.h>
using namespace std;

template <typename T>
struct binary_indexed_tree {
    int N;
    vector<int> BIT;
    binary_indexed_tree(int N) : N(N), BIT(N + 1, 0) {
    }
    void add(int i) {
        i++;
        while (i <= N) {
            BIT[i]++;
            i += i & -i;
        }
    }
    int sum(int i) {
        int ans = 0;
        while (i > 0) {
            ans += BIT[i];
            i -= i & -i;
        }
        return ans;
    }
    int sum(int L, int R) {
        return sum(R) - sum(L);
    }
};