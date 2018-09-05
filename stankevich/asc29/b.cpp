#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int v[MAXN];
int nxt[MAXN];
int memo[MAXN];

pair <int, int> st[30 * MAXN];
int L[30 * MAXN];
int R[30 * MAXN];

int cnt = 0;
int root = -1;

void setnode (int & x) {
	if (x == -1)
		x = cnt++;
}

void update (int & nd, int l, int r, pair <int, int> x, int p) {
	setnode (nd);

	if (l == r) {
		st[nd] = x;
		return;
	}

	int mid = (l + r) >> 1;

	if (p <= mid) {
		update (L[nd], l, mid, x, p);
		if (R[nd] + 1)
			st[nd] = max (st[L[nd]], st[R[nd]]);
		else
			st[nd] = st[L[nd]];
	} else {
		update (R[nd], mid + 1, r, x, p);
		if (L[nd] + 1)
			st[nd] = max (st[L[nd]], st[R[nd]]);
		else
			st[nd] = st[R[nd]];
	}
}

pair <int, int> res;
pair <int, int> query (int nd, int l, int r, int ll, int rr) {
	if (rr < ll) return res;

	// cout << "Query em " << nd << " (" << l << ", " << r << ")" << endl;

	if (nd == -1) return res;
	if (ll <= l && r <= rr) return st[nd];
	if (rr < l || r < ll) return res;

	int mid = (l + r) >> 1;

	return max (query (L[nd], l, mid, ll, rr), query (R[nd], mid + 1, r, ll, rr));
}


int main () {

	freopen ("financial.in", "r", stdin);
	freopen ("financial.out", "w", stdout);

	memset (L, -1, sizeof L);
	memset (R, -1, sizeof R);

	res = make_pair (0, -1);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; ++i) scanf ("%d", v + i);

	for (int i = n - 1; i >= 0; --i) {
		pair <int, int> bst = query (root, 0, 1e9, v[i] + k, 1e9);
		bst = max (bst, query (root, 0, 1e9, 0, v[i] - k));

		// cout << i << " -> " << bst.first << " " << bst.second << endl;

		memo[i] = bst.first + 1;
		nxt[i] = bst.second;

		update (root, 0, 1e9, make_pair (memo[i], i), v[i]);
	}

	pair <int, int> ans = query (root, 0, 1e9, 0, 1e9);

	cout << ans.first << endl;

	while (ans.second != -1) {
		printf ("%d ", v[ans.second]);
		ans.second = nxt[ans.second];
	}

	cout << endl;

	return 0;
}