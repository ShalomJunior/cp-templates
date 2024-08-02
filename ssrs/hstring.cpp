#include<bits/stdc++.h>
using namespace std;

const int LOG = 18;
const long long M30 = ((long long)1 << 30) - 1;
const long long M31 = ((long long)1 << 31) - 1;
const long long MOD = ((long long)1 << 61) - 1;
const long long BASE = 10000000;
unsigned long long modulo(unsigned long long x) {
    unsigned long long xu = x >> 61;
    unsigned long long xd = x & MOD;
    unsigned long long res = xu + xd;
    if (res >= MOD) {
        res -= MOD;
    }
    return res;
}
unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned long long au = a >> 31;
    unsigned long long ad = a & M31;
    unsigned long long bu = b >> 31;
    unsigned long long bd = b & M31;
    unsigned long long mid = au * bd + ad * bu;
    unsigned long long midu = mid >> 30;
    unsigned long long midd = mid & M30;
    return modulo(au * bu * 2 + midu + (midd << 31) + ad * bd);
}

struct rolling_hash {
    vector<long long> POW, S;
    rolling_hash(string s) {
        int N = s.size();
        POW.resize(N + 1);
        POW[0] = 1;
        for (int i = 0; i < N; i++) {
            POW[i + 1] = mul(POW[i], BASE);
        }
        S.resize(N + 1);
        S[N] = 0;
        for (int i = N - 1; i >= 0; i--) {
            S[i] = modulo(mul(S[i + 1], BASE) + s[i]);
        }
    }
    long long get(int L, int R) {
        return modulo(S[L] + MOD - mul(S[R], POW[R - L]));
    }
};