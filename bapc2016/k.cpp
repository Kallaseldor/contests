#include <bits/stdc++.h>
using namespace std;

const long long MOD = 123456789;
const int MAXN = 1123456;

long long memo[MAXN];
long long sum[MAXN];

int main () {

	int n, s;
	cin >> n >> s;

	memo[0] = 1;
	sum[0] = 1;

	for (int i = 1; i <= n; ++i) {
		memo[i] = sum[i - 1];
		if (i > s) memo[i] -= sum[i - s - 1];

		memo[i] += MOD;
		while (memo[i] >= MOD) memo[i] -= MOD;

		sum[i] = sum[i - 1] + memo[i];
		while (sum[i] >= MOD) sum[i] -= MOD;
	}

	long long ans = 0;
	for (long long i = 1; i <= s; ++i) {
		ans += memo[n - i] * i;
		ans %= MOD;
	}

	cout << ans << endl;

	return 0;
}