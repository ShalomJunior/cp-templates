#include <bits/stdc++.h>
using namespace std;

const int N = 26;
const int INF = 1e9;
vector<int> get(string s, string p, bool flag) {
    if (flag) {
        reverse(s.begin(), s.end());
        reverse(p.begin(), p.end());
    }
    int n = s.length();
    int m = p.length();
    vector<vector<int>> idx(N);
    for (int i = 0; i < n; i++) {
        idx[s[i] - 'a'].push_back(i);
    }
    vector<int> ans(m + 1, n);
    ans[0] = -1;
    int start = 0;
    for (int i = 0; i < m; i++) {
        int j = p[i] - 'a';
        auto it = lower_bound(idx[j].begin(), idx[j].end(), start);
        if (it == idx[j].end()) break;
        ans[i + 1] = *it;
        start = ans[i + 1] + 1;
    }
    if (flag) {
        vector<int> temp(m + 1);
        for (int i = 0; i <= m; i++) {
            if (ans[i] == -1)
                temp[i] = n;
            else if (ans[i] == INF)
                temp[i] = -1;
            else
                temp[i] = n - 1 - ans[i];
        }
        ans = temp;
    }
    return ans;
}