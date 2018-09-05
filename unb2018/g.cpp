#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50;

vector <int> g[MAXN];

bitset <50> adj[MAXN];

unordered_map <long long, int> lst;
bitset <50> v[1123456];

int main () {

	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf ("%d %d", &a, &b);
		g[--b].push_back (--a);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			adj[i][g[i][j]] = true;
		}
	}

	// cout << "Adj" << endl;
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		cout << adj[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	// cout << endl << endl;

	v[0].reset();
	v[0][0] = true;
	for (int p = 0; p <= k; ++p) {
		v[p + 1].reset();
		long long val = 0;
		for (int i = 0; i < n; ++i)
			if (v[p][i])
				val |= (1LL << i);

		//cout << p << " " << val << endl;

		if (lst.count (val)) {
			int c = lst[val];
			// cout << "Get: " << c + ((k - p) % (p - c)) << endl;
			v[k] = v[c + ((k - p) % (p - c))];
			break;
		}

		lst[val] = p;

		for (int i = 0; i < n; ++i)
			if (v[p][i])
				v[p + 1] |= adj[i];

	}

	cout << v[k].count() << endl;
	if (v[k].count() == 0) return 0;
	for (int i = 0; i < n; ++i) {
		if (v[k][i]) printf ("%d ", i + 1);
	}

	cout << endl;

	return 0;
}