// Esquece. Eu errei no calculo da complexidade. Se nao me engano, esse ficou
// O(NM log(N+M)) ou algo do tipo. A solucao com DP fica O(M^2) ou O(NM)
// dependendo da implementacao. Talvez a solucao dessa nao seja com PQ after all.

#include <bits/stdc++.h>
using namespace std;

struct node{
	int energy, cost, id;
	node() {}
	node(int _energy, int _cost, int _id) {
		energy = _energy;
		cost = _cost;
		id = _id;
	}
};

vector<node> v[112345];
pair<int, int> levelPos[112345];
int fases[112345];
bool vis[112345];
int best[112345];

void insertLoja(int pos, int energy, int cost, int id) {
	levelPos[id] = make_pair(pos, v[pos].size());
	v[pos].push_back(node(energy, cost, id));
}

int main() {

	int n, m;
	cin >> n >> m;
	
	memset(vis, 0, sizeof vis);
	memset(best, -1, sizeof best);

	for (int i = 1; i <= n; ++i) scanf("%d", fases + i);

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		insertLoja(a, b, c, i);
	}

	priority_queue<pair<int, int> > pq;

	for (int i = 0; i < v[1].size(); ++i) {
		pq.push(make_pair(-v[1][i].cost, v[1][i].id));
	}

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int id = pq.top().second;
		pq.pop();

		if (vis[id]) continue;
		vis[id] = true;

		pair<int, int> level = levelPos[id];
		node curr = v[level.first][level.second];

		int energy = curr.energy;

		bool win = true;

		//Passar pela primeira fase
		if (fases[level.first] <= energy) energy -= fases[level.first];
		else continue;

		//Passar pelo resto
		for (int i = level.first + 1; i <= n; ++i) {
			//Olhar as lojas
			for (int j = 0; j < v[i].size(); ++j) {
				// Da pra melhorar aqui vendo se a energia da loja
				// eh menor que a energia atual. Mas dai precisaria
				// ordenar as lojas de cada vase e soh colocar um id
				// pra cada fase depois de ler tudo.
				pq.push(make_pair(-cost - v[i][j].cost, v[i][j].id));
			}

			//Passar pela fase
			if (fases[i] <= energy) energy -= fases[i];
			else {
				win = false;
				break;
			}

			if (best[i] > energy) {
				win = false;
				break;
			} else {
				best[i] = energy;
			}
		}

		if (win) {
			cout << cost << endl;
			return 0;
		}

	}



	cout << "-1" << endl;

	return 0;
}