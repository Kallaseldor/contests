#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e12;

/*

Min Cost - Deu errado. Acho que o código q eu peguei tava cagado.

typedef int val; // type of flow
typedef long long num; // type of cost
const int N = 112, M =  2750 * 2; const num eps = 0;
struct mcmf {
	int es[N], to[M], nx[M], en = 2, pai[N], seen[N], tempo, qu[N];
	val fl[M], cp[M], flow; num cs[M], d[N], tot;
	val spfa(int s, int t) {
		tempo++; int a = 0, b = 0;
		for(int i = 0; i < N; i++) d[i] = numeric_limits<num>::max();
		d[s] = 0; qu[b++] = s; seen[s] = tempo;
		while(a != b) {
			int u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
			for(int e = es[u]; e; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
		}
		if(d[t] == numeric_limits<num>::max()) return false;
		val mx = numeric_limits<val>::max();
		for(int u = t; u != s; u = to[pai[u]])
			mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
		tot += d[t] * val(mx);
		for(int u = t; u != s; u = to[pai[u]])
			fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
		return mx;
	}
	// public $
	num min_cost(int s, int t) {
		tot = 0; flow = 0;
		while(val a = spfa(s, t)) flow += a;
		return tot;
	}
	void add_edge(int u, int v, val c, num s) {
		cout << u << " " << v << " " << c << " " << s << endl;
		fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
		fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
	}
	void reset_flow() { memset(fl, 0, sizeof(val) * en); }
	void init(int n) { en = 2; memset(es, 0, sizeof(int) * n); } // XXX must be called
};

*/

int n, m;
int v[75];
vector <int> g[75];
bool can[75][75];		// can[i][j] = true -> DE j consegue roubar o cofre i

// Descobre quem consegue roubar o cofre X
void calc (int x) {

	vector <int> s, t;
	vector <int> sp, tp;

	for (int i = 0; i < (g[x].size() >> 1); ++i)
		s.push_back (g[x][i]);

	for (int i = 0; i < (1 << s.size()); ++i) {
		int val = 0;
		for (int j = 0; j < s.size(); ++j)
			if (i & (1 << j)) val += s[j];
		sp.push_back (val);
	}

	for (int i = g[x].size() >> 1; i < g[x].size(); ++i)
		t.push_back (g[x][i]);

	for (int i = 0; i < (1 << t.size()); ++i) {
		int val = 0;
		for (int j = 0; j < t.size(); ++j)
			if (i & (1 << j)) val += t[j];
		tp.push_back (val);
	}

	/*
	cout << "\nS" << endl;
	for (int i = 0; i < s.size(); ++i)
		cout << s[i] << " ";

	cout << "\nSP" << endl;
	for (int i = 0; i < sp.size(); ++i)
		cout << sp[i] << " ";


	cout << "\nT" << endl;
	for (int i = 0; i < s.size(); ++i)
		cout << t[i] << " ";

	cout << "\nTP" << endl;
	for (int i = 0; i < sp.size(); ++i)
		cout << tp[i] << " ";

	cout << endl;
	*/

	sort (sp.begin(), sp.end());
	sort (tp.begin(), tp.end());

	for (int i = 0; i < m; ++i) {
		can[x][i] = false;
		int l = 0, r = tp.size() - 1;
		while (l < sp.size() && r >= 0) {
			if (v[i] == sp[l] + tp[r]) {
				can[x][i] = true;
				break;
			} else if (v[i] < sp[l] + tp[r])
				--r;
			else
				++l;
		}
	}

	return;
}

// Kuhn's Algorithm (Maximum Matching)
// Time Complexity: O(|V| * |E|)

const int MAXN = 300;

vector<int> g2[MAXN];	// Vertices from A numbered 0 to n - 1
int match[MAXN];		// Vertices from B numbered 0 to m - 1
bool vis[MAXN];

bool dfs(int u) {
	if (vis[u]) return false;
	vis[u] = true;

	for (int i = 0; i < g2[u].size(); ++i) {
		int v = g2[u][i];
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}

	return false;
}

int kuhn(int n) {
	memset(match, -1, sizeof match);
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		memset(vis, false, sizeof vis);
		if (dfs(i)) ans += v[i];
	}

	return ans;
}

int main () {

	int o;
	cin >> o;

	while (o--) {
		scanf ("%d %d", &m, &n);

		for (int i = 0; i < m; ++i) scanf ("%d", v + i);

		sort (v, v + m);
		reverse (v, v + m);

		for (int i = 0; i < n; ++i) {
			g[i].clear();
			
			int sz;
			scanf ("%d", &sz);
			for (int j = 0; j < sz; ++j) {
				int a;
				scanf ("%d", &a);
				g[i].push_back (a);
			}
		}

		for (int i = 0; i < n; ++i) calc (i);

		for (int i = 0; i < m; ++i) {
			g2[i].clear();
			for (int j = 0; j < n; ++j)
				if (can[j][i]) g2[i].push_back (j);
		}

		printf ("%d\n", kuhn (m));

		/*
		// Printando CAN[i][j]
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				cout << i << " " << j << " " << can[i][j] << endl;

		cout << endl;

		

		Modelando o Flow - Deu errado. Acho que eh a implementacao do flow la em cima

		// 0 -> Source
		// 1 - N -> cofres
		// 1 + N - M + N -> Death Eaters
		// M + N + 1 -> Sink



		mcmf f;
		for (int i = 1; i <= n; ++i) f.add_edge (0, i, 1, 0);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (can[i][j]) f.add_edge (1 + i, 1 + n + j, 1, 0);
			}
		}

		for (int i = 0; i < m; ++i)
			f.add_edge (1 + n + i, n + m + 1, 1, INF - (long long) v[i]);

		f.init (112);
		f.reset_flow();

		long long ans = f.min_cost (0, m + n + 1);
		while (ans > 0) ans -= INF;
		ans *= -1;

		printf ("%lld\n", ans);
		*/
	}

	return 0;
}