#include <bits/stdc++.h>
using namespace std;

#define MAXN 112345

int n, m;
vector<pair<long long, int> > lojas[MAXN];	//Energia / Custo

long long v[MAXN];	//Energia necessaria pra passar do lvl 1. 1-indexado.
long long s[MAXN];	//Soma acumulada de V

struct node {
	int cost, pos;
	long long energy;
	node() {}
	node (int _c, int _p, long long _e) { cost = _c; pos = _p; energy = _e; }
	bool operator < (const node nd) const {
		if (cost != nd.cost) return (cost > nd.cost);
		return (energy + s[pos - 1] > (nd.energy + s[nd.pos - 1]));
	}
};

int main() {
	
	cin >> n >> m;

	for (int i = 1; i <= n; ++i) scanf("%lld", &v[i]);
	s[0] = 0;
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + v[i];


	for (int i = 0; i < m; ++i) {
		int a, c;
		long long b;
		scanf("%d %lld %d", &a, &b, &c);
		lojas[a].push_back(make_pair(b, c));
	}


	priority_queue<node> pq;

	for (int i = 1; i <= n; ++i) {

		if (i == 1 || !pq.empty()) {
			//Custo pra chegar ate aqui
			int val;
			if (i == 1) val = 0;
			else val = pq.top().cost;
			
			//Lojas novas
			for (int j = 0; j < lojas[i].size(); ++j) {
				pq.push(node(lojas[i][j].second + val, i, lojas[i][j].first));

			}
		}

		// Tirar a galera inutil. Se tiver alguém de util, break
		while (!pq.empty()) {
			node nd = pq.top();
			if (nd.energy >= s[i] - s[nd.pos - 1])
				break;
			else
				pq.pop();
		}
	}

	if (pq.empty()) {
		cout << "-1" << endl;
	} else {
		cout << pq.top().cost << endl;
	}

	return 0;
}