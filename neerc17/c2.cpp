#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

struct Edge {
	int from, to, id;
	bool flag;

	Edge () {
		flag = false;
	}

	Edge (int _from, int _to, int _id) {
		from = _from; to = _to; id = _id; flag = false;
	}
};

vector <Edge> edges;
vector <int> g[MAXN];
vector <int> rev[MAXN];

bool vis[MAXN];

void dfs1 (int x) {
	vis[x] = true;
	for (int i = 0; i < g[x].size(); ++i) {
		Edge & e = edges[g[x][i]];
		int y = e.to;

		if (vis[y]) continue;

		e.flag = true;
		dfs1 (y);
	}
}

void dfs2 (int x) {
	vis[x] = true;
	for (int i = 0; i < rev[x].size(); ++i) {
		Edge & e = edges[rev[x][i]];
		int y = e.from;

		if (vis[y]) continue;
		e.flag = true;
		dfs2 (y);
	}
}

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	int o;
	cin >> o;

	while (o--) {
		int n, m;
		cin >> n >> m;

		edges.clear();
		for (int i = 0; i < n; ++i) {
			g[i].clear();
			rev[i].clear();
		}

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			g[--a].push_back (edges.size());
			rev[--b].push_back (edges.size());
			edges.push_back (Edge (a, b, edges.size()));
		}

		for (int i = 0; i < n; ++i) vis[i] = false;
		dfs1 (0);
	
		for (int i = 0; i < n; ++i) vis[i] = false;
		dfs2 (0);

		int cnt = m - 2 * n;
		for (int i = 0; i < edges.size(); ++i) {
			if (!edges[i].flag && cnt > 0) {
				printf ("%d %d\n", edges[i].from + 1, edges[i].to + 1);
				--cnt;
			}
		}


	}

	return 0;
}