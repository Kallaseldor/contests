#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;
const int LOGN = 50;

vector <int> g[MAXN];

long long val[MAXN];
long long hval[MAXN];

struct query () {
	int op, x, y;
	query () {}
	query (int _op, int _x) {
		op = _op; x = _x;
	}

	query () (int _op, int _x, int _y) {
		op = _op, x = _x; y = _y;
	}
};

vector <query> queries;

// First: Height      Second: Node
pair<int, int>  memo[MAXN][LOGN];	// Sparse Table
vector<pair<int, int> > v;			// DFS order
int pos[MAXN];						// Pos[i] = first appearance of i in v

vector<int> g[MAXN];				// Tree

void build (int n) {
	for (int i = 0; i < n; ++i) {
		memo[i][0] = v[i];
	}

	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 0; (1 << j) + i - 1 < n; ++i)
			if (memo[i][j - 1].first < memo[i + (1 << (j - 1))][j - 1].first)
				memo[i][j] = memo[i][j - 1];
			else
				memo[i][j] = memo[i + (1 << (j - 1))][j - 1];


}

int query (int l, int r) {
	l = pos[l];
	r = pos[r];

	int j = (int) log2(r - l + 1);
	
	if (memo[l][j].first < memo[r - (1 << j) + 1][j].first)
		return memo[l][j].second;
	else
		return memo[r - (1 << j) + 1][j].second;
}

void dfslca(int x, int pai, int h) {
	pos[x] = v.size();
	v.push_back(make_pair(h, x));

	for (int i = 0; i < g[x].size(); ++i) {
		if (g[x][i] == pai) continue;
		dfslca(g[x][i], x, h + 1);
		v.push_back(make_pair(h, x));
	}
}

void setup(int root) {
	dfs(root, -1, 0);
	build(v.size());
}

void dfs (int x, int pai, int h) {
	val[x] = hval[h];

	for (int i = 0; i < g[x].size(); ++i) {
		
	}
}

int main () {

	int n, m;
	cin >> n >> m;

	for (int i = 1; i < n; ++i) {
		int a, b;
		scanf ("%d %d", &a, &b);
		g[--a].push_back (--b);
		g[b].push_back (a);
	}

	return 0;
}