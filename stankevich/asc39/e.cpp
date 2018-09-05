#include <bits/stdc++.h>
using namespace std;

const int MAXN = 512;
const int MAXP = 112;
const int MAXH = 52;

const long long MOD = 1e9 + 7;

long long memo[MAXN][MAXP][MAXH];

long long solve (int n, int s, int h) {
	if (h <= 0) return 0;
	if (s < 0) return 0;
	if (n < 0) return 0;
	if (n == 0) return (s == h) ? 1 : 0;

	long long & p = memo[n][s][h];
	if (p + 1) return p;

	p = 0;

	for (int nh = 1; nh <= 30; ++nh)
		p += (1LL + (abs (h - nh))) * solve (n - nh, s - 2 - abs (h - nh), nh);

	p %= MOD;
	return p;
}

int main () {

	// freopen ("expedition.in", "r", stdin);
	// freopen ("expedition.out", "w", stdout);

	memset (memo, -1, sizeof memo);

	int n;
	cin >> n;

	int p = 4 * n;

	for (int i = 1; i <= n; ++i)
		p = min (p, 2 * (i + (n / i) + (n % i ? 1 : 0)));

	long long ans = 0;

	for (int i = 1; i <= 30; ++i)
		ans += solve (n - i, p - 2 - i, i);

	cout << ans % MOD << endl;

	return 0;
}