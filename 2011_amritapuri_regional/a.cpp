#include <bits/stdc++.h>
using namespace std;

int v[512][512];
int memo[512][512];

int n, m;

bool solve (int x) {

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			memo[i][j] = 0;

	memo[0][0] = x;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int & p = memo[i][j];
			if (i && memo[i - 1][j])
				p = max (p, memo[i - 1][j] + v[i][j]);

			if (j && memo[i][j - 1])
				p = max (p, memo[i][j - 1] + v[i][j]);
		}
	}

	return memo[n - 1][m - 1] != 0;
}

int main () {

	int o;
	cin >> o;

	while (o--) {
		cin >> n >> m;

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				scanf ("%d", &v[i][j]);

		int l = 1, r = 1e7;
		int best = 1;

		while (l <= r) {
			int mid = (l + r) >> 1;
			if (solve (mid)) {
				best = mid;
				r = mid - 1;
			} else
				l = mid + 1;
		}
		

		printf ("%d\n", best);
	}

	return 0;
}