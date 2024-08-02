#include <bits/stdc++.h>
using namespace std;

vector<int> generate(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return { 0 };
    if (n == 1) return { 0, arr[0] };
    vector<int> L(arr.begin(), arr.begin() + n / 2);
    vector<int> R(arr.begin() + n / 2, arr.end());
    vector<int> Lsums = generate(L);
    vector<int> Rsums = generate(R);
    vector<int> sums;
    for (int sum1 : Lsums) {
        for (int sum2 : Rsums) {
            sums.push_back(sum1 + sum2);
        }
    }
    sort(sums.begin(), sums.end());
    sums.resize(unique(sums.begin(), sums.end()) - sums.begin());
    return sums;
}

//This one is like 2 time faster dans the first one
vector<int> generate(const vector<int>& arr) {
    int n = arr.size();
    vector<int> ans = { 0 };
    for (int i = 0; i < n; i++) {
        vector<int> temp;
        for (auto& c : ans) temp.push_back(c + arr[i]);
        vector<int> res;
        merge(ans.begin(), ans.end(),
            temp.begin(), temp.end(),
            back_inserter(res));
        res.resize(unique(res.begin(), res.end()) - res.begin());
        ans = res;
    }
    return ans;
}