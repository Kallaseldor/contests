#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;
const long long MOD = 1e9 + 7;

int n;
int v[MAXN];

// 1  -> Max
// 0  -> Nadahhhh
// -1 -> Min

long long p[MAXN];

long long seq () {
	long long ans = 0;
	int ma = 0, mi = 0, bon = 0;

	for (int i = 0; i < n; ++i) {
		if (v[i] == 1) {
			ans += p[bon + ma] * (p[mi] - 1);
			ans %= MOD;
		} else if (v[i] == -1) {
			ans += p[bon + mi] * (p[ma] - 1);
			ans %= MOD;
		} else {
			long long temp = p[bon] * (p[mi] - 1);
			temp %= MOD;
			ans += temp * (p[ma] - 1);
			ans %= MOD;
		}

		if (v[i] == 1) ma++;
		else if (v[i] == -1) mi++;
		else bon++;
	}

	return ans;
}

long long str () {
	long long ans = 0;
	int mini = 0, maxi = 0;
	int r = 0;

	for (int l = 0; l < n; ++l) {
		while (r < n && (mini == 0 || maxi == 0)) {
			if (v[r] == 1) maxi++;
			else if (v[r] == -1) mini++;

			++r;
		}

		if (maxi && mini) ans += n - r + 1;

		if (v[l] == 1) --maxi;
		else if (v[l] == -1) --mini;
	}

	return ans % MOD;
}

int main () {

	p[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		p[i] = p[i - 1] * 2;
		if (p[i] >= MOD) p[i] -= MOD;
	}

	int o;
	cin >> o;

	while (o--) {
		cin >> n;

		for (int i = 0; i < n; ++i) scanf ("%d", v + i);
		
		int mini = MOD;
		int maxi = -1;

		for (int i = 0; i < n; ++i) {
			mini = min (v[i], mini);
			maxi = max (maxi, v[i]);
		}

		if (mini == maxi) {
			long long a1 = n;
			a1 *= n + 1;
			a1 >>= 1;
			a1 %= MOD;

			long long a2 = 1;
			while (n--) {
				a2 <<= 1LL;
				a2 %= MOD;
			}

			a2 += MOD - 1;
			a2 %= MOD;

			printf ("%lld %lld\n", a1, a2);
			continue;
		}

		for (int i = 0; i < n; ++i) {
			if (v[i] == maxi) v[i] = 1;
			else if (v[i] == mini) v[i] = -1;
			else v[i] = 0;
		}

		printf ("%lld %lld\n", str(), seq());
	}

	return 0;
}