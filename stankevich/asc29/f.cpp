#include <bits/stdc++.h>
using namespace std;

const long long base = 1009;
const long long MOD = 1e9 + 7;
const int M = 200000;

long long fexp (long long b, long long e) {
	if (e == 0) return 1;
	if (e == 1) return b;

	if (e & 1) return b * fexp (b, e - 1);
	long long a = fexp (b, e >> 1);
	return a * a;
}

vector <long long> fs[212];
vector <long long> ft[212];

int main () {

	string s, t;
	cin >> s >> t;

	int off = s.size() - t.size();

	for (int i = 0; i < s.size(); ++i)
		fs[s[i]].push_back (i + 1);

	for (int i = 0; i < s.size(); ++i)
		for (int j = 0; j < fs.size(); ++j)
			fs[s[i]] = fexp (base, j) * (i + 1);

	for (int i = 0; i < s.size(); ++i)

	for (long long i = 0; i < t.size(); ++i)
		ft[t[i]].push_back (make_pair (i, i * fexp (base, ft[t[i]].size()) ));



	return 0;
}