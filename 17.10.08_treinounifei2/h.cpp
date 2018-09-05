#include <bits/stdc++.h>
using namespace std;

int val[11234];
bool vis[112345];
// bool memo[11234][112345];
set<int> memo;	//gcdval * 1e4 + pos

vector<int> g[11234];

int ans = 0;

const int mul = 10000;

// void solve(int pos, int gcdval) {
// 	//cout << pos << endl;
// 	if (!vis[gcdval]) {
// 		vis[gcdval] = true;
// 		ans++;
// 		//cout << "ans++ em " << gcdval << endl;
// 	}

// 	if (memo[pos][gcdval]) return;
// 	memo[pos][gcdval] = true;

// 	for (int i = 0; i < g[pos].size(); ++i) {
// 		int v = g[pos][i];
// 		solve(v, __gcd(gcdval, val[v]));
// 	}

// 	return;

// }

void solve(int pos, int gcdval) {
	if (!vis[gcdval]) {
		vis[gcdval] = true;
		ans++
	}

	int key = gcdval * 10000 + pos;
	if (memo.count(key)) return;
	memo.insert(key);

	for (int i = 0; i < g[pos].size(); ++i) {
		int v = g[pos][i];
		solve(v, __gcd(gcdval, val[v]));
	}

	return;

}

int main() {

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) scanf("%d", val + i);

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	for (int i = 0; i < n; ++i) {
		solve(i, val[i]);
	}

	cout << ans << endl;

	return 0;
}