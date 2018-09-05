#include <bits/stdc++.h>
using namespace std;

int n, m;
int cost[212];

vector<int> g[212];

vector<pair<int, int> > pacotinhos;	//F: Bolachas
									//S: Custo

bool vis[212];
int saldo, custo;
int id;

void dfs(int u) {
	//cout << "u = " << u << endl;
	if (vis[u]) return;
	vis[u] = true;
	if (u < n) {
		saldo++;
	} else {
		saldo--;
	}

	custo += cost[u];

	for (int i = 0; i < g[u].size(); ++i)
		dfs(g[u][i]);

	return;

}

int main() {


	int r, w;
	memset(vis, false, sizeof vis);

	cin >> n >> m >> r >> w;

	for (int i = 0; i < n + m; ++i) scanf("%d", &cost[i]);
	
	for (int i = 0; i < r; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		g[a].push_back(n + b);
		g[n + b].push_back(a);
	}

	// cout << "aqui comeca G" << endl;
	// for (int i = 0; i < n + m; ++i) {
	// 	cout << i << " - ";
	// 	for (int j = 0; j < g[i].size(); ++j) {
	// 		cout << g[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << "acabou!" << endl;

	id = 0;
	for (int i = 0; i < n + m; ++i) {
		if (!vis[i]) {
			//printf("i = %d\n", i);
			saldo = 0; custo = 0;
			id++;
			dfs(i);
			pacotinhos.push_back(make_pair(saldo, custo));
		}
	}

	// for (int i = 0; i < m; ++i) {
	// 	if (!vis[i]) {

	// 		//printf("ii = %d\n", i);
	// 		saldo = 0; custo = 0;
	// 		id++;
	// 		dfs(i);
	// 		pacotinhos.push_back(make_pair(saldo, custo));
	// 	}
	// }

	//Fazer a mochila, dar memset e printar resposta
	int memo[w + 1];

	memset(memo, 0, sizeof memo);

	for (int i = 0; i < pacotinhos.size(); ++i) {
		for (int j = w; j >= 0; --j) {
			if (j < pacotinhos[i].second) break;
			memo[j] = max(memo[j], -pacotinhos[i].first + memo[j - pacotinhos[i].second]);
		}
	}

	int a1 = memo[w];

	memset(memo, 0, sizeof memo);

	for (int i = 0; i < pacotinhos.size(); ++i) {
		for (int j = w; j >= 0; --j) {
			if (j < pacotinhos[i].second) break;
			memo[j] = max(memo[j], pacotinhos[i].first + memo[j - pacotinhos[i].second]);
		}
	}

	// for (int i = 0; i < pacotinhos.size(); ++i) {
	// 	cout << "pacotinhos[" << i << "] = " << pacotinhos[i].first << " " << pacotinhos[i].second << endl;
	// }

	cout << a1 + n << " " << memo[w] + m << endl;
	return 0;
}