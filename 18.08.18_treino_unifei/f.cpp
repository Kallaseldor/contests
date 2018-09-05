#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123;
long long x[MAXN], y[MAXN];

int main () {

	int n;
	for (int tt = 1; true; ++tt) {
		cin >> n;
		if (n == 0) break;

		for (int i = 0; i < n; ++i) scanf ("%lld %lld", x + i, y + i);
		sort (x, x + n);
		sort (y, y + n);

		long long tx = x[(n - 1) >> 1];
		long long ty = y[(n - 1) >> 1];

		long long ans = 0;

		for (int i = 0; i < n; ++i) {
			ans += abs (tx - x[i]);
			ans += abs (ty - y[i]);
		}

		printf ("Case %d: (%lld,%lld) %lld\n", tt, tx, ty, ans);
	}

	return 0;
}