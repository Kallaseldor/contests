#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1123456;

int cnt;
int id[MAXN], sz[MAXN];

void setup (int n) {
	cnt = n;
	for (int i = 0; i < n; ++i) {
		id[i] = i;
		sz[i] = 1;
	}
}

// Returns id of set that contains p
int find (int p) {
	int root = p;
	while (root != id[root])
		root = id[root];
	
	while (p != root) {
		int newp = id[p];
		id[p] = root;
		p = newp;
	}

	return root;
}

// Merges sets containing x and y
void merge (int x, int y) {
	int i = find(x);
	int j = find(y);
	if (i == j) return;

	if (sz[i] > sz[j])
		swap(i, j);  
		
	id[i] = j;
	sz[j] += sz[i];
	--cnt;
}

vector <int> g[MAXN];

pair <int, int> v[MAXN];	// First = Mando
							// Second = Tempo

int main () {

	freopen ("jackpot.in", "r", stdin);
  	freopen ("jackpot.out", "w", stdout);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf ("%d %d", &a, &b);
		--a; --b;
		a <<= 1; b <<= 1;
		if (a < b) swap (a, b);

		g[a].push_back (b);
	}

	for (int i = 0; i < (n << 1); ++i) v[i] = make_pair (-1, -1);
	setup (n << 1);

	for (int x = 0; x < (n << 1); x += 2) {
		int opp = -1;
		int me = -1;

		set <int> tim;
		for (int i = 0; i < g[x].size(); ++i) {
			int y = g[x][i];
			y = find (y);

			// Se a cor de Y foi decidida pelo meu oponente
			if (v[y].first != (x & 2))
				if (opp + 1 && v[y].second != v[opp].second) {
					cout << ((x & 2) ? "Alice" : "Bob") << " " << (x >> 1) + 1 << endl;
					return 0;
				} else
					opp = y;

			// Se a cor de Y foi decidida por mim
			if (v[y].first == (x & 2)) {
				if (tim.count (v[y].second ^ 1)) {
					cout << ((x & 2) ? "Alice" : "Bob") << " " << (x >> 1) + 1 << endl;
					return 0;
				}
				tim.insert (v[y].second);
				if (!(me + 1) || v[y].second < v[me].second)
					me = y;
			}

		}

		/*cout << " === " << endl;
		cout << "X = " << x << "  Size = " << g[x].size() << endl;
		cout << "me = " << me << "  v[me] = " << v[me].first << " " << v[me].second << endl;
		cout << "opp = " << opp << " v[opp] = " << v[opp].first << " " << v[opp].second << endl;
		*/

		if (opp + 1) {
			int xopp = opp ^ 1;
			xopp = find (xopp);

			v[x] = v[xopp];
			v[x ^ 1] = v[opp];

			merge (x, xopp);
			merge (x ^ 1, opp);

			if (me + 1) {
				if (v[opp].second > v[me].second) {
					cout << ((x & 2) ? "Alice" : "Bob") << " " << (x >> 1) + 1 << endl;
					return 0;
				} else {
					for (int i = 0; i < g[x].size(); ++i) {
						int y = g[x][i];
						int xy = find (y ^ 1);
						y = find (y);

						v[y] = v[opp];
						v[xy] = v[xopp];

						merge (y, opp);
						merge (xy, xopp);
					}
				}
			}
		} else if (me + 1) {
			int xme = me ^ 1;
			xme = find (xme);

			v[x] = v[xme];
			v[x ^ 1] = v[me];

			merge (x, xme);
			merge (x ^ 1, me);

			for (int i = 0; i < g[x].size(); ++i) {
				int y = g[x][i];
				int xy = find (y ^ 1);
				y = find (y);

				v[y] = v[me];
				v[xy] = v[xme];

				merge (y, me);
				merge (xy, xme);
			}
		} else {
			v[x] = make_pair (x & 2, x);
			v[x ^ 1] = make_pair (x & 2, x ^ 1);
		}
	}

	cout << "Tie" << endl;

	return 0;
}

	/*
	for (int x = 0; x < n; ++x) {

		int opp = -1;
		int me = -1;

		set<int> tim;
		for (int i = 0; i < g[x].size(); ++i) {
			int y = g[x][i];
			y = find (y);

			// Se o meu oponente tem um cara ligado a mim
			if (v[y].first + 1 && v[y].first != (x & 2)) {
				if (opp + 1 && v[y].second != v[opp].second) {
					cout << ((x & 2) ? "Alice" : "Bob") << " " << (x >> 1) + 1 << endl;
					return 0;
				} else {
					opp = y;
				}
			}

			// Se eu tenho um cara ligado a mim
			if (v[y].first + 1 && v[y].first == (x & 2)) {
				if (me + 1 && v[y].second != v[me].second) {
					if (v[y].second < v[me].second)
						me = y;
				} else {
					me = y;
				}
			}
		}

		cout << " === " << endl << "X = " << x << endl << "me = " << me << "  v[me] = " << v[me].first << " " << v[me].second << endl << "opp = " << opp << " v[opp] = " << v[opp].first << " " << v[opp].second << endl;

		if (opp + 1) {
			v[x] = v[opp];
			merge (x, opp);
			if (me + 1) {
				if (v[opp].second > v[me].second) {
					cout << ((x & 2) ? "Alice" : "Bob") << " " << (x >> 1) + 1 << endl;
					return 0;
				} else {
					for (int i = 0; i < g[x].size(); ++i) {
						int y = g[x][i];
						
						if (v[find (y)].first + 1) {
							v[y] = v[opp];
							v[find (y)] = v[opp];
							merge (y, opp);
						}
					}
				}
			}
		} else if (me + 1) {
			v[x] = v[me];
			merge (x, me);
			for (int i = 0; i < g[x].size(); ++i) {
				int y = g[x][i];

				if (v[find (y)].first + 1) {
					v[find (y)] = v[me];
					v[y] = v[me];
					merge (y, me);
				}
			}
		} else {
			v[x] = make_pair (x & 2, x);
		}
	}

	cout << "Tie" << endl;



	return 0;
}
*/