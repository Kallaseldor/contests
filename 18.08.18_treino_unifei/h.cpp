#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11234;
vector <pair <int, int> > g[MAXN];
int dist[MAXN];

vector <int> v;
int mat[10][10];
long long memo[10][1 << 10];

int target;
long long solve (int x, int msk) {
	if (__builtin_popcount (msk) == target) return mat[x][0];

	long long & p = memo[x][msk];
	if (p + 1) return p;

	p = 0x3F3F3F3F;

	for (int i = 0; i < v.size(); ++i) {
		if (!(msk & (1 << i)))
			p = min (p, mat[x][i] + solve (i, msk | (1 << i)));
	}

	return p;
}

int n;

void dijkstra (int s) {
	priority_queue <pair <int, int> > pq;
	pq.push (make_pair (0, s));

	for (int i = 0; i < n; ++i)
		dist[i] = 0x3F3F3F3F;

	dist[s] = 0;

	while (!pq.empty()) {
		int d = -pq.top().first;
		int x = pq.top().second;

		pq.pop();

		if (d > dist[x]) continue;

		for (int i = 0; i < g[x].size(); ++i) {
			int y = g[x][i].first;
			int nd = d + g[x][i].second;

			if (nd < dist[y]) {
				dist[y] = nd;
				pq.push (make_pair (-nd, y));
			}
		}
	}
}

int main () {

	int testcase;
	cin >> testcase;

	while (testcase--) {

		int m;
		scanf ("%d %d", &n, &m);
		++n;

		for (int i = 0; i < n; ++i) g[i].clear();

		for (int i = 0; i < m; ++i) {
			int a, b, c;
			scanf ("%d %d %d", &a, &b, &c);
			g[a].push_back (make_pair (b, c));
			g[b].push_back (make_pair (a, c));
		}

		int k;
		scanf ("%d", &k);

		v.clear();
		v.push_back (0);
		for (int i = 0; i < k; ++i) {
			int a;
			scanf ("%d", &a);
			v.push_back (a);
		}

		++k;

		for (int i = 0; i < k; ++i) {
			dijkstra (v[i]);
			for (int j = 0; j < k; ++j) {
				mat[i][j] = dist[v[j]];
			}
		}

		int w;
		scanf ("%d", &w);

		for (int i = k; i >= 0; --i) {
			memset (memo, -1LL, sizeof memo);
			target = i;
			if (solve (0, 1) <= w) {
				printf ("%d\n", i - 1);
				break;
			}

		}
	}

	return 0;
}