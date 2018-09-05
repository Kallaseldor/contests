#include <bits/stdc++.h>
using namespace std;

#define INF 0x3F3F3F3F

struct node{
	int cap, cost, id;

	bool operator< (const node nd) const {
		if (cap != nd.cap) return cap < nd.cap;
		if (cost != nd.cost) return cost < nd.cost;
		return id < nd.id;
	}
};

struct student {
	int val, id;

	bool operator< (const student nd) const {
		if (val != nd.val) return val < nd.val;
		return id < nd.id;
	}
};

student v[5123];
node build[5123];

int memo[5123][5123];

int n, m;
int solve(int st, int pos) {

	if (st == n) return 0;
	if (pos == m) return INF;

	int &p = memo[st][pos];
	if (p != -1) return p;

	p = 0;
	p = solve(st, pos + 1);
	
	if (build[pos].cap >= v[st].val) p = min(p, solve(st + 1, pos + 1) + build[pos].cost);

	return p;
}

int bb[5123];

void back(int st, int pos, int ans) {
	if (ans == 0) return;

	if (solve(st, pos + 1) != ans) {
		bb[v[st].id] = build[pos].id;
		back(st + 1, pos + 1, solve(st + 1, pos + 1));
	} else {
		back(st, pos + 1, ans);
	}
}

int main() {

	cin >> n >> m;

	for (int i = 0; i < n; ++i) { scanf("%d", &v[i].val	); v[i].id = i;}

	sort(v, v + n);

	for (int i = 0; i < m; ++i) scanf("%d", &build[i].cap);
	for (int i = 0; i < m; ++i) scanf("%d", &build[i].cost);
	for (int i = 0; i < m; ++i) build[i].id = i + 1;
	sort(build, build + m);

	memset(memo, -1, sizeof memo);

	if (solve(0, 0) == INF) cout << "impossible\n";
	else {
		back(0, 0, solve(0, 0));
		for (int i = 0; i < n; ++i) {
			printf("%d%c", bb[i], (i == n - 1) ? '\n' : ' ');
		}
	}

	return 0;
}