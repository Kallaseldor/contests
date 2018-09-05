#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112;
const long long LINF = 0x3F3F3F3F3F3F3F3FLL;

long long mat[512][512];
vector <pair <int, int> > v;	// First -> Tower
								// Second -> Floor

vector <pair <int, int> > used[MAXN];	// First -> Floor
										// Second -> Id in V

// X = Tower, Y = Floor
int blow (int x, int y) {
	int l = 0, r = used[x].size() - 1;
	int best = l;

	while (l <= r) {
		int mid = (l + r) >> 1;
		if (used[x][mid].first <= y) {
			best = mid;
			l = mid + 1;
		} else
			r = mid - 1;
	}

	return used[x][best].second;
}

// X = Tower, Y = Floor
int bhi (int x, int y) {
	int l = 0, r = used[x].size() - 1;
	int best = r;

	while (l <= r) {
		int mid = (l + r) >> 1;
		if (used[x][mid].first >= y) {
			best = mid;
			r = mid - 1;
		} else
			l = mid + 1;
	}

	return used[x][best].second;
}

// Floors  -  0 -> F - 1
// Towers  -  0 -> N - 1
int main () {

	int o;
	cin >> o;

	while (o--) {
		int n, f, m;
		cin >> n >> f >> m;

		// Setup
		for (int i = 0; i < n + 5; ++i) used[i].clear();
		v.clear();
		
		for (int i = 0; i < (n + n + m + m + 5); ++i)
			for (int j = 0; j < (n + n + m + m + 5); ++j)
				mat[i][j] = LINF;


		// Ground Floor
		for (int i = 0; i < n; ++i)
			v.push_back (make_pair (i, 0));

		// Distance between Towers
		for (int i = 0; i < n - 1; ++i) {
			mat[i][i + 1] = 1;
			mat[i + 1][i] = 1;
		}

		mat[n - 1][0] = 1;
		mat[0][n - 1] = 1;

		// Last Floors of Towers
		for (int i = 0; i < n; ++i)
			v.push_back (make_pair (i, f - 1));

		// Adding Edges
		for (int i = 0; i < m; ++i) {
			int a, b, c, d, e;
			scanf ("%d %d %d %d %d", &a, &b, &c, &d, &e);
			--a; --b; --c; --d;

			v.push_back (make_pair (a, b));
			v.push_back (make_pair (c, d));

			mat[v.size() - 1][v.size() - 2] = e;
			mat[v.size() - 2][v.size() - 1] = e;
		}

		// Adding distance between nodes of the same tower
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v.size(); ++j)
				if (v[i].first == v[j].first)
					mat[i][j] = abs (v[i].second - v[j].second);

		// Adding nodes to used
		for (int i = 0; i < v.size(); ++i)
			used[v[i].first].push_back (make_pair (v[i].second, i));

		for (int i = 0; i < n; ++i)
			sort (used[i].begin(), used[i].end());

		for (int i = 0; i < v.size(); ++i)
			mat[i][i] = 0;

		// Floyd-Warshall
		for (int k = 0; k < v.size(); ++k)
			for (int i = 0; i < v.size(); ++i)
				for (int j = 0; j < v.size(); ++j)
					mat[i][j] = min (mat[i][j], mat[i][k] + mat[k][j]);
	
		int q;
		cin >> q;
		
		while (q--) {
			int a, b, c, d;
			scanf ("%d %d %d %d", &a, &b, &c, &d);
			--a; --b; --c; --d;

			int s1, s2, t1, t2;
			s1 = blow (a, b);
			s2 = bhi (a, b);
			t1 = blow (c, d);
			t2 = bhi (c, d);

			long long ans = mat[s1][t1] + abs (v[s1].second - b) + abs (v[t1].second - d);
			ans = min (ans, mat[s1][t2] + abs (v[s1].second - b) + abs (v[t2].second - d));
			ans = min (ans, mat[s2][t2] + abs (v[s2].second - b) + abs (v[t2].second - d));
			ans = min (ans, mat[s2][t1] + abs (v[s2].second - b) + abs (v[t1].second - d));
			
			printf ("%lld\n", ans);
		}

	}

	return 0;
}