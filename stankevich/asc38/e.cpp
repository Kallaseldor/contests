#include <bits/stdc++.h>
using namespace std;

struct node;
vector <node> treap[2];

struct node {
	int x, y, cnt, tr;
	int l, r;

	node (int _x, int _tr) {
		tr = _tr;
		x = _x;
		y = abs ((rand() << 16) ^ rand());
		cnt = 1;
		l = -1;
		r = -1;
	}

	void recalc () {
		cnt = 1;
		if (l + 1) cnt += treap[tr][l].cnt;
		if (r + 1) cnt += treap[tr][r].cnt;
	}
};

int merge (int l, int r, int tr) {
	if (!(l + 1) || !(r + 1)) return l + 1 ? l : r;
	if (treap[tr][l].y < treap[tr][r].y) {
		treap[tr][l].r = merge (treap[tr][l].r, r, tr);
		treap[tr][l].recalc();
		return l;
	} else {
		treap[tr][r].l = merge (l, treap[tr][r].l, tr);
		treap[tr][r].recalc();
		return r;
	}
}

void split (int v, int x, int & l, int & r, int tr) {
	l = -1; r = -1;
	if (!(v + 1)) return;
	if (treap[tr][v].x < x) {
		split (treap[tr][v].r, x, treap[tr][v].r, r, tr);
		l = v;
	} else {
		split (treap[tr][v].l, x, l, treap[tr][v].l, tr);
		r = v;
	}

	treap[tr][v].recalc();
}

int root[2] = {-1, -1};

void insert (int x, int tr) {
	int l, r;
	split (root[tr], x, l, r, tr);
	treap[tr].push_back (node (x, tr));
	root[tr] = merge (merge (l, treap[tr].size() - 1, tr), r, tr);
}

void erase (int x, int tr) {
	int l, m, r;
	split (root[tr], x, l, m, tr);
	split (m, x + 1, m, r, tr);
	root[tr] = merge (l, r, tr);
}

int getSize(int nd, int tr) {
	return nd + 1 ? treap[tr][nd].cnt : 0;
}

int query (int nd, int val, int tr) {
	if (nd == -1) return 0;

	if (treap[tr][nd].x <= val)
		return query (treap[tr][nd].r, val, tr) + getSize (treap[tr][nd].l, tr) + 1;

	return query (treap[tr][nd].l, val, tr);
}

int main () {

	srand (time (NULL));

	int n;
	cin >> n;

	int d = 0;

	for (int i = 0; i < n; ++i) {
		int op;
		scanf ("%d", &op);

		if (op == 1) {
			int l, r;
			scanf ("%d %d", &l, &r);

			l += d; r += d;

			insert (l, 0);
			insert (r + 1, 1);
		} else {
			int x;
			scanf ("%d", &x);

			int ans = query (root[0], x, 0) - query (root[1], x, 1);
			printf ("%d\n", ans);
			d = ans;
		}
	}

	return 0;
}