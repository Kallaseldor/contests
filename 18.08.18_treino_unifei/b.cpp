#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int cnt;	// Amount of connected components
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

int main () {

	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;

		setup (n);

		while (m--) {
			char c;
			int x, y;
			scanf (" %c %d %d", &c, &x, &y);
			--x; --y;

			if (c == 'C')
				printf ("%c\n", find (x) == find (y) ? 'S' : 'N');
			else
				merge (x, y);
		}
	}

	return 0;
}