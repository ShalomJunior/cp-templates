#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static const int K = 26;
    static const int N = 1e6 + 5;
    struct vtx {
        int to[K];
        int go[K];
        int val;
        int par;
        int sufflink = -1;
        int matches;
        int match_id;
    } trie[N];
    int num_vtx = 1;

    void init() {
        for (int i = 0; i < N; i++) fill(trie[i].go, trie[i].go + K, -1);
    }

    int to(int v, int k) {
        if (!trie[v].to[k]) {
            trie[num_vtx].val = k;
            trie[num_vtx].par = v;
            trie[v].to[k] = num_vtx++;
        }
        return trie[v].to[k];
    }

    void insert(string s, bool rev, int id) {
        if (rev) reverse(s.begin(), s.end());
        int cur = 0;
        for (char c : s) cur = to(cur, c - 'a');
        trie[cur].matches++;
        trie[cur].match_id = id;
    }

    int get_link(int v) {
        if (trie[v].sufflink == -1) {
            if (v == 0 || trie[v].par == 0) {
                trie[v].sufflink = 0;
            }
            else {
                trie[v].sufflink = go(get_link(trie[v].par), trie[v].val);
            }
            if (v != 0) {
                get_link(trie[v].sufflink);
                trie[v].matches += trie[trie[v].sufflink].matches;
                if (!trie[v].match_id) trie[v].match_id = trie[trie[v].sufflink].match_id;
            }
        }
        return trie[v].sufflink;
    }

    int go(int v, int x) {
        if (trie[v].go[x] == -1) {
            if (trie[v].to[x]) {
                trie[v].go[x] = trie[v].to[x];
            }
            else if (v == 0) {
                trie[v].go[x] = 0;
            }
            else {
                trie[v].go[x] = go(get_link(v), x);
            }
        }
        return trie[v].go[x];
    }

    void build() {
        for (int v = 0; v < num_vtx; v++) get_link(v);
    }

    void debug(int v) {
        cout << "vtx " << v << endl;
        for (int i = 0; i < K; i++) {
            if (trie[v].to[i]) {
                cout << (char)('a' + i) << ' ' << trie[v].to[i] << endl;
            }
        }
        cout << "parent: " << trie[v].par << endl;
        cout << "match id " << trie[v].match_id << endl;
        for (int i = 0; i < K; i++) {
            if (trie[v].to[i]) debug(trie[v].to[i]);
        }
    }
} A, B;