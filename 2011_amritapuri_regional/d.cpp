#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2550;

vector<int> g[MAXN];	// Vertices from A numbered 0 to n - 1
int match[MAXN];		// Vertices from B numbered 0 to m - 1
bool vis[MAXN];

bool dfs(int u) {
	if (vis[u]) return false;
	vis[u] = true;

	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}

	return false;
}

int kuhn(int n) {
	memset(match, -1, sizeof match);
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		memset(vis, false, sizeof vis);
		if (dfs(i)) ans++;
	}

	return ans;
}


int v[MAXN];

int main () {

	int o;
	cin >> o;

	while (o--) {
		int n;
		cin >> n;

		for (int i = 0; i < n; ++i) scanf ("%d", v + i);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int id = i * n + j;
				g[id].clear();
				g[id].push_back (i);
				g[id].push_back (j);
			}
		}

		printf ("%d\n", kuhn (n * n));
	}

	return 0;
}