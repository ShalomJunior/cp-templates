#include <bits/stdc++.h>
#define Mine pair<int,int>
#define F first
#define S second
using namespace std;

const int N = 1e5;
bitset<N> prime;
vector<int> primes;
void prepare() {
    primes.reserve(N);
    for (int i = 2; i < N; i++) prime.set(i);
    for (int i = 2; i < N; i++) {
        if (!prime[i]) continue;
        primes.push_back(i);
        for (long long j = 1LL * i * i; j < N; j += i) prime.reset(j);
    }
}

void _dec(int n, map<int, int>& div) {
    int i = 0;
    while (n > 1 && i < primes.size()) {
        if (n < N && prime[n]) {
            div[n]++;
            return;
        }
        while (n % primes[i] == 0) {
            div[primes[i]]++;
            n /= primes[i];
        }
        i++;
    }
    if (n > 1) div[n]++;
}

void dec(int n, vector<Mine>& div) {
    int i = 0;
    while (n > 1 && i < primes.size()) {
        if (n < N && prime[n]) {
            div.push_back({ 1, n });
            return;
        }
        Mine add = { 0, primes[i] };
        while (n % primes[i] == 0) {
            add.F++;
            n /= primes[i];
        }
        if (add.F) div.push_back(add);
        i++;
    }
    if (n > 1) div.push_back({ 1, n });
}
