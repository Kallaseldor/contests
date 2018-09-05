#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112;
const long long MOD = 1e9 + 7;

long long fastexp (long long b, long long e) {
	if (e == 0) return 1LL;
	if (e & 1) return (b * (fastexp (b, e - 1))) % MOD;
	long long a = fastexp (b, e >> 1);
	return (a * a) % MOD;
}

long long memo[MAXN];
long long fat[MAXN];
long long inv[MAXN];

long long cc (int x, int y) {
	long long ans = fat[x] * inv[y];
	ans %= MOD;
	ans *= inv[x - y];
	ans %= MOD;
	return ans;
}

int main () {

	fat[0] = 1;
	inv[0] = 1;

	for (long long i = 1; i < MAXN; ++i) {
		fat[i] = fat[i - 1] * i;
		fat[i] %= MOD;
		inv[i] = fastexp (fat[i], MOD - 2);
	}

	int n;
	cin >> n;

	string s, t;
	cin >> s >> t;

	int k = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '.' && t[i] == 'o') {
			cout << 0 << endl;
			return 0;
		}

		if (s[i] == 'o' && t[i] == '.')
			++k;
	}
	
	memo[0] = 1;

	for (int i = 1; i <= k; ++i) {
		for (int j = 0; j < i; ++j) {
			memo[i] += memo[j] * cc (k - j, i - j);
			memo[i] %= MOD;
		}

		// cout << i << " " << memo[i] << endl;
	}

	if (k == 0) cout << 0 << endl;
	else cout << memo[k] << endl;


	return 0;
}