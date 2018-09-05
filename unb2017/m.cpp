#include <bits/stdc++.h>
using namespace std;

#define MAXN 112345

int st[4 * MAXN];
int v[MAXN];

void build(int nd, int l, int r) {
	if (l == r) {st[nd] = v[l]; return;}
	int mid = (l + r) >> 1;
	int nxt = nd << 1;

	build(nxt, l, mid);
	build(nxt + 1, mid + 1, r);

	st[nd] = __gcd(st[nxt], st[nxt + 1]);
}

int query(int nd, int l, int r, int i, int j) {
	if (i > r || j < l) return 0;
	if (i <= l && r <= j) {return st[nd];}

	int mid = (l + r) >> 1;
	int nxt = nd << 1;
	int a1 = query(nxt, l, mid, i, j);
	int a2 = query(nxt + 1, mid + 1, r, i, j);

	int ret;
	
	if (a1 && a2) ret = __gcd(a1, a2);
	else if (a1) ret = a1;
	else if (a2) ret = a2;
	else r = 0;
	
	// printf("(%d %d) - %d\n", l, r, ret);
	return ret;
}

int main() {

	int o;
	cin >> o;

	while (o--) {

		int n, m;
		cin >> n >> m;

		for (int i = 0; i < n; ++i) scanf("%d", v + i);
		memset(st, 0, sizeof st);
		build(1, 0, n - 1);

		while (m--) {
			int l, r;
			scanf("%d %d", &l, &r);

			// cout << "---------------" << m << "--------------" << endl;

			printf("%d", query(1, 0, n - 1, l - 1, r - 1));
			if (m != 0) printf(" ");
		}
		printf("\n");

	}
	return 0;
}