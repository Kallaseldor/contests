#include <bits/stdc++.h>
using namespace std;

#define INF 0x3F3F3F3F

int num = 0;

struct node{
	int id;
	int pai;
	int jump;
	map<char, int> nxt;

	node() {}
	node(int _pai) {
		id = num++;
		jump = -1;
		pai = _pai;
	}

};

node root;
vector<node> trie;
vector<int> dist;
int final[112345];	// Para os M carinhas, fala qual o ultimo id dele

void dfs() {
	for (int i = 0; i < trie.size(); ++i)
		dist.push_back(INF);

	queue<pair<int, int> > q;
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		int u = q.front().first;
		int d = q.front().second;
		q.pop();

		if (dist[u] != INF) continue;
		dist[u] = d;
		node nd = trie[u];
		d++;

		// Visitando os filhos
		for (map<char, int>::iterator it = nd.nxt.begin(); it != nd.nxt.end(); ++it)
			q.push(make_pair(it->second, d));

		// Visitando o pai
		q.push(make_pair(nd.pai, d));

		// Visitando o jump
		if (u != 0) q.push(make_pair(nd.jump, d));
		//cout << "Aqui tem jump pra " << nd.jump << endl;
	}

	return;
}

int main() {

	int n, m;
	cin >> n >> m;

	root = node(0);
	trie.push_back(root);

	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		int curr = 0;

		// Colocar os carinhas na Trie
		for (int j = 0; j < s.size(); ++j) {
			if (trie[curr].nxt.count(s[j])) curr = trie[curr].nxt[s[j]];
			else {
				// Inserir o node na Trie
				trie[curr].nxt[s[j]] = num;
				trie.push_back(node(curr));
				curr = num - 1;
			}
		}

		// Voltar preenchendo o jump
		int last = curr;
		// cout << "com i igual a " << i << " o id do meu last eh " << last << endl;
		curr = 0;
		for (int j = 0; j < s.size(); ++j) {
			if (trie[curr].jump == -1) trie[curr].jump = last;
			curr = trie[curr].nxt[s[j]];
		}
		if (trie[last].jump == -1) trie[last].jump = last;
	}

	// Colocar a galera que nao ta no dicionario
	for (int i = 0; i < m; ++i) {
		string s;
		cin >> s;
		int curr = 0;

		// Colocar os carinhas na Trie
		for (int j = 0; j < s.size(); ++j) {
			if (trie[curr].nxt.count(s[j])) curr = trie[curr].nxt[s[j]];
			else {
				// Inserir o node na Trie
				trie[curr].nxt[s[j]] = num;
				trie.push_back(node(curr));
				curr = num - 1;
			}
		}

		final[i] = curr;
	}

	dfs();

	for (int i = 0; i < m; ++i) {
		printf("%d\n", dist[final[i]]);
	}

	return 0;
}