#include <bits/stdc++.h>
using namespace std;

int n;
pair <int, int> memo[20][1 << 18];

pair <int, int> solve (int x, int msk) {
	if (x == n) return make_pair (0, -1);

	pair <int, int> & p = memo[x][msk];

	if (p.first + 1) return p;

	bool w = false, b = false;
	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (msk & (1 << y)) w = true;
		else b = true;
	}

	if (w && b) return p = make_pair (2 - (x & 1))
}

int main () {

	int m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf ("%d %d", &a, &b);
		--a; --b;

		if (a < b) swap (a, b);
		g[a].push_back (b);
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < (1 << n); ++j)
			memo[i][j] = make_pair (-1, -1);



	return 0;
}