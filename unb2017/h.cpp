#include <bits/stdc++.h>
using namespace std;

int l, r, c;
long long a[2123];
long long b[2123];

const long long MOD = 1e9 + 7;

void add(long long &a, long long b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return;
}

void mult() {

	memset(b, 0, sizeof b);
	for (int i = 0; i <= c; ++i) {
		for (int j = 0; j <= c; ++j) {
			if (i + j > c) break;
			add(b[i + j], (a[i] * a[j]) % MOD);
		}
	}

	for (int i = 0; i <= c; ++i) { a[i] = b[i]; } //printf("%d - %lld\n", i, a[i]);}
	return;
}

void solve(int n) {

	if (n == 1) {
		memset(a, 0, sizeof a);
		for (int i = l; i <= r; ++i) a[i] = 1;
		return;
	}

	if (n & 1) {
		solve(n - 1);
		memset(b, 0, sizeof b);
		for (int i = l; i <= r; ++i) {
			for (int j = 0; j <= c; ++j) {
				if (i + j > c) break;
				add(b[i + j], a[j]);
			}
		}

		for (int i  = 0; i <= c; ++i) a[i] = b[i];
		return;
	}

	solve(n >> 1);
	mult();
	return;

}
/*
long long solve(int pos, int w) {
	if (pos == n)
		if (w == 0) return 1;
		else return 0;

	if (w < 0) return 0;

	long long &p = memo[pos][w];
	if (p != -1LL) return p;

	p = 0;
	for (int i = l; i <= min(w, r); ++i) {
		add(p, solve(pos + 1, w - i));
	}

	return p;
}
*/

int main() {

	int o;
	cin >> o;
	while (o--) {
		int n;

		cin >> n >> c >> l >> r;
		solve(n);

		cout << a[c] << endl;

	}

	return 0;
}