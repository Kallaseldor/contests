#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;

int memo[112][112][2][2];
int solve (int n, int m, bool black, bool turn) {
	if (n == 0 || m == 0) return 0;
	if (n == 1 && m == 1) return (black ^ turn ^ 1) ? 1 : -1;

	int & p = memo[n][m][black][turn];
	if (p != INF) return p;

	if (turn) {
		p = -INF;
		for (int i = 1; i <= m; ++i) {
			if ((i & 1) && (n & 1)) {
				p = max (p, solve (n, m - i, black ^ 1, turn ^ 1) + (black ? 1 : -1));
			} else {
				p = max (p, solve (n, m - i, black ^ (i & 1), turn ^ 1));
			}
		}
	} else {
		p = INF;
		for (int i = 1; i <= n; ++i) {
			if ((i & 1) && (m & 1)) {
				p = min (p, solve (n - i, m, black, turn ^ 1) - ((n & 1) ^ (i & 1) ^ black ? 1 : -1));
			} else {
				p = min (p, solve (n - i, m, black, turn ^ 1));
			}
		}
	}

	return p;
}

int main () {

	int n, m;
	cin >> n >> m;

	memset (memo, INF, sizeof memo);

	cout << solve (n, m, 1, 1) << endl;

	return 0;
}