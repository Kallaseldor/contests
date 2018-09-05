#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123456;
const int MAXV = 1123456;
const int INF = 0x3F3F3F3F;

int v[MAXN];

int nxt[MAXN];
int st[4 * MAXN];

void build (int nd, int l, int r) {
	if (l == r) {
		st[nd] = nxt[l];
		return;
	}

	int mid = (l + r) >> 1;

	build (nd << 1, l, mid);
	build ((nd << 1) + 1, mid + 1, r);

	st[nd] = max (st[nd << 1], st[(nd << 1) + 1]);
}

void update (int nd, int l, int r, int x, int val) {
	if (l == r) {
		st[nd] = val;
		return;
	}

	int mid = (l + r) >> 1;
	if (x <= mid)
		update (nd << 1, l, mid, x, val);
	else
		update ((nd << 1) + 1, mid + 1, r, x, val);

	st[nd] = max (st[nd << 1], st[(nd << 1) + 1]);
}

int query (int nd, int l, int r, int ll, int rr) {
	if (rr < l || r < ll) return -INF;
	if (ll <= l && r <= rr) return st[nd];

	int mid = (l + r) >> 1;
	return max (query (nd << 1, l, mid, ll, rr), query ((nd << 1) + 1, mid + 1, r, ll, rr));
}

set <int> has;
set <int> occ[MAXV];

int main () {

	int n, m;

	while (cin >> n >> m) {
		for (set <int> :: iterator it = has.begin(); it != has.end(); ++it)
			occ[*it].clear();
		has.clear();

		for (int i = 1; i <= n; ++i) scanf ("%d", v + i);
		for (int i = 1; i <= n; ++i) {
			occ[v[i]].insert (0);
			occ[v[i]].insert (n + 1);
			
			set <int> :: iterator it = occ[v[i]].lower_bound (i);
			--it;

			nxt[i] = *it;
			
			occ[v[i]].insert (i);
			has.insert (v[i]);
		}

		build (1, 1, n);

		while (m--) {
			char op;
			scanf (" %c", &op);

			if (op == 'E') {
				int x;
				scanf ("%d", &x);

				printf ("%d\n", x - query (1, 1, n, 1, x));
			} else {
				int x, val;
				scanf ("%d %d", &x, &val);

				has.insert (val);
				occ[val].insert (0);
				occ[val].insert (n + 1);

				// Referente ao valor antigo de v[x]
				set <int> :: iterator it = occ[v[x]].upper_bound (x);
				int oldl = *it;

				occ[v[x]].erase (x);
				--it;

				int oldr = *it;

				update (1, 1, n, oldl, oldr);

				// Referente ao valor novo de v[x]
				it = occ[val].upper_bound (x);

				update (1, 1, n, *it, x);
				--it;
				update (1, 1, n, x, *it);

				v[x] = val;
				occ[val].insert (x);
			}
		}

	}

	return 0;
}