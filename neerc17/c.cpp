#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

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

struct Edge {
	int from, to, id;
	bool flag;

	Edge () {
		flag = false;
	}

	Edge (int _from, int _to, int _id) {
		from = _from; to = _to; id = _id; flag = false;
	}
};

vector <int> g[MAXN];
vector <Edge> edges;	// Todas as arestas
stack <int> order;
bool vis[MAXN];

void dfs (int x) {
	// cout << "DFS ( " << x << " )" << endl;
	vis[find (x)] = true;

	for (int i = 0; i < g[x].size(); ++i) {
		Edge & e = edges[g[x][i]];
		int y = e.to;

		// cout << x << " -> " << y << endl;

		if (find (x) == find (y)) {
			// cout << "Caiu no caso 1" << endl;
			continue;
		}
		if (vis[find (y)]) {
			// cout << "Caiu no caso 2" << endl;
			order.push (e.id);
			int target = find (y);

			while (edges[order.top()].from != target) {
				// cout << "MERGE! " << edges[order.top()].from << " " << target << endl;
				// cout << " - " << edges[order.top()].from << " " << edges[order.top()].to << endl;
				merge (edges[order.top()].from, target);
				edges[order.top()].flag = true;
				order.pop();
			}

			edges[order.top()].flag = true;
			continue;
		}


		// cout << "Caiu no caso 3" << endl;
		// cout << " + " << e.from << " " << e.to << endl;
		order.push (e.id);
		dfs (y);
	}
}

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	int o;
	cin >> o;

	while (o--) {

		// LEMBRAR DE DAR CLEAR EM TUDO QUE EH GLOBAL ANTES DE TESTAR/SUBMETER

		int n, m;
		cin >> n >> m;

		for (int i = 0; i < n; ++i)
			g[i].clear();

		setup (n);
		while (!order.empty())
			order.pop();
		edges.clear();

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			g[--a].push_back (edges.size());
			edges.push_back (Edge (a, --b, edges.size()));
			vis[a] = false; vis[b] = false;
		}

		dfs (0);

		int cnt = m - 2 * n;
		for (int i = 0; i < edges.size(); ++i) {
			if (!edges[i].flag && cnt > 0) {
				printf ("%d %d\n", edges[i].from + 1, edges[i].to + 1);
				--cnt;
			}
		}
		// LEMBRAR DE DAR CLEAR EM TUDO QUE EH GLOBAL ANTES DE TESTAR/SUBMETER

	}

	return 0;
}