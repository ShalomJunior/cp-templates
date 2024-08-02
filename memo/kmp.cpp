#include<bits/stdc++.h>
using namespace std;

vector<int> kmp_table(string& p){
	int n = p.size();
	vector<int> table(n);
	int k = 0;
	for (int i = 1; i < n; i++){
		while (k > 0 && p[i] != p[k - 1]) k = table[k - 1];
		if (p[i] == p[k]) k++;
		table[i] = k;
	}
	return table;
}

vector<int> kmp(string& s, string& p){
	int m = s.size();
	int n = p.size();
	auto table = kmp_table(p);
	vector<int> id;
	int k = 0;
	for (int i = 0; i < n; i++){
		while (k > 0 && s[i] != p[k]) k = table[k - 1];
		if (s[i] == p[k])k++;
		if (k == n){
			id.push_back(i - m + 1);
			k = table[k - 1];
		}
	}
	return id;
}