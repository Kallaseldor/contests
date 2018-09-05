#include <bits/stdc++.h>
using namespace std;

int n, k;
long long memo[1 << 15][16];

long long solve (int msk, int lst) {
	if  (__builtin_popcount (msk) == n) return 1;
	
	long long & p = memo[msk][lst];
	if (p + 1) return p;

	p = 0;
	if (lst == n) {
		for (int i = 0; i < n; ++i) {
			p += solve (1 << i, i);
		}
	} else {
		for (int i = 0; i < n; ++i) {
			if (msk & (1 << i)) continue;
			if (abs (lst - i) <= k)
				p += solve (msk | (1 << i), i);
		}
	}

	return p;
}

int main () {
	int o;
	cin >> o;

	while (o--) {
		cin >> n >> k;

		memset (memo, -1, sizeof memo);
		cout << solve (0, n) << endl;
	}
}