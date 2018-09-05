#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11234;
const double EPS = 1e-9;

struct Edge {
	int x, y, id;
	double c;

	bool has;

	Edge () { has = false; }
	Edge (int _x, int _y, double _c, int _id) {
		x = _x; y = _y; c = _c; id = _id; has = false;
	}

	int get (int z) {
		return (x == z) ? y : x;
	}
};

int n, m;
vector <Edge> edges;
vector <int> g[MAXN];

double dist[MAXN];

vector <int> path;

bool dijkstra (double b) {
	for (int i = 0; i < n; ++i)
		dist[i] = HUGE_VAL;

	dist[0] = 0.0;

	priority_queue <pair <double, int> > pq;

	pq.push (make_pair (0.0, 0));

	while (!pq.empty()) {
		int x = pq.top().second;
		double d = -pq.top().first;
		pq.pop();

		if (dist[x] > d) continue;

		for (int i = 0; i < g[x].size(); ++i) {
			Edge e = edges[g[x][i]];
			int y = e.get (x);
			double nd = e.c + (e.has ? -b : b);
			nd = max (nd, 1.0) + d;

			if (dist[y] > nd) {
				dist[y] = nd;
				pq.push (make_pair (- nd, y));
			}
		}
	}

	double ans = 0.0;
	for (int i = 0; i < path.size(); ++i) {
		double d = edges[path[i]].c + (edges[path[i]].has ? -b : b);
		d = max (d, 1.0);
		ans += d;
	}

	if (ans - dist[n - 1] < EPS) return true;
	return false;
}

void addEdge (int x, int y, int c) {
	g[x].push_back (edges.size());
	g[y].push_back (edges.size());

	edges.push_back (Edge (x, y, (double) c, edges.size()));
}

int main () {

	freopen ("lateagain.in", "r", stdin);
	freopen ("lateagain.out", "w", stdout);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf ("%d %d %d", &a, &b, &c);
		addEdge (a - 1, b - 1, c);
	}

	int q;
	scanf ("%d", &q);
	while (q--) {
		int a;
		scanf ("%d", &a);
		path.push_back (--a);
		edges[a].has = true;
	}

	double l = 0, r = 2e7;

	for (int o = 0; o < 75; ++o) {
		double mid = (l + r) / 2.0;
		if (dijkstra (mid))
			r = mid;
		else
			l = mid;
	}

	printf ("%.9lf\n", l);
	for (int i = 0; i < edges.size(); ++i) {
		double d = edges[i].c + (edges[i].has ? -l : l);
		d = max (d, 1.0);
		printf ("%.9lf ", d);
	}

	cout << endl;

	return 0;
}