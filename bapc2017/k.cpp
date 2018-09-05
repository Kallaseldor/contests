#include <bits/stdc++.h>
using namespace std;

vector <int> g[1123];
vector <int> order;
bool vis[1123];

void dfs (int x) {
	vis[x] = true;

	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (vis[y]) continue;
		dfs (y);
	}
	
	order.push_back (x);
}

int main () {

	int n;
	cin >> n;

	memset (vis, false, sizeof vis);

	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < n; ++j) {
			if (s[j] == '1') g[i].push_back (j);
		}
	}

	dfs (0);

	if (order.size() == n) {
		for (int i = 0; i < n; ++i)
			printf ("%d%c", order[i], (i == n - 1) ? '\n' : ' ');
	} else
		printf ("impossible\n");

	return 0;
}