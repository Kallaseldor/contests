#include <bits/stdc++.h>
using namespace std;

int n, f;
vector<pair<int, int> > g2[112345];
bool target[112345];

vector<int> g[112345];
int pai[112345];

int memo[112345][2];

int solve(int pos, bool canEnd) {
	if (g[pos].size() == 0) {
		if (canEnd) return 0;
		return (target[pos] ? pai[pos] : 0);
	}

	int &p = memo[pos][canEnd];
	if (p != -1) return p;
	p = 0;

	if (canEnd) {
		int mdiff = -1;
		for (int i = 0; i < g[pos].size(); ++i) {
			p += solve(g[pos][i], 0);
			
			if (solve(g[pos][i], 0) - solve(g[pos][i], 1) > mdiff) {
				mdiff = solve(g[pos][i], 0) - solve(g[pos][i], 1);
			}
		}

		p -= mdiff;
	
	} else {
		for (int i = 0; i < g[pos].size(); ++i) {
			p += solve(g[pos][i], 0);
		}
		if (p != 0 || target[pos]) p += pai[pos];
	}

	return p;
}

void prep(int pos, int x) {
	for (int i = 0; i < g2[pos].size(); ++i) {
		if (g2[pos][i].first == x) pai[pos] = g2[pos][i].second;
		else {
			g[pos].push_back(g2[pos][i].first);
			prep(g2[pos][i].first, pos);
		}
	}
}

int main() {

	cin >> n >> f;
	
	if (n == 1) { cout << "0\n"; return 0;}

	for (int i = 0; i < n - 1; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		g2[a].push_back(make_pair(b, c));
		g2[b].push_back(make_pair(a, c));
	}


	memset(target, false, sizeof target);
	for (int i = 0; i < f; ++i) {
		int a;
		scanf("%d", &a);
		target[a] = true;
	}

	memset(memo, -1, sizeof memo);

	prep(1, 0);

	cout << solve(1, 1) << endl;

	// for (int i = 1; i <= n; ++i) {
	// 	cout << "i = " << i << "    -   " << memo[i][0] << " " << memo[i][1] << endl;
	// }

	return 0;
}