#include <bits/stdc++.h>
using namespace std;

int main () {

	long long n;
	while (cin >> n) {
		if (n == 0) break;

		long long ans = 0;

		for (int i = 1; i <= n; ++i) {
			long long k = (n >> 1) + (n & i & 1);
			ans += ((i + i + k - 1LL) * k) >> 1LL;
		}

		cout << ans << '\n';
	}

	return 0;
}