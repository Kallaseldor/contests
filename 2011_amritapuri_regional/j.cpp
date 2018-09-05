#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;

int n, m;
char v[512][512];
int dist[512][512];
vector <pair <int, int> > st;

int vx[] = {1, 0, -1, 0};
int vy[] = {0, 1, 0, -1};

struct node {
	int y, x, d;
	char who;

	node () {}
	node (int _x, int _y, int _d, char _who) {
		x = _x; y = _y; who = _who; d = _d;
	}
};

bool isValid (int i, int j, int d) {
	if (i < 0 || i >= n || j < 0 || j >= m) return false;
	if (v[i][j] == '#') return false;
	if (dist[i][j] < d) return false;
	return true;
}

void bfs () {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			dist[i][j] = INF;

	queue <node> q;
	for (int i = 0; i < st.size(); ++i)
		q.push (node (st[i].first, st[i].second, 0, v[st[i].first][st[i].second]));

	while (!q.empty()) {
		node curr = q.front();
		q.pop();

		// Checar se tem *
		if (v[curr.x][curr.y] == '*') continue;

		for (int k = 0; k < 4; ++k) {
			node nxt = curr;
			nxt.x += vx[k];
			nxt.y += vy[k];
			nxt.d++;

			if (!isValid (nxt.x, nxt.y, nxt.d)) continue;

			int x = nxt.x;
			int y = nxt.y;
			int d = nxt.d;
			char who = nxt.who;

			dist[x][y] = d;

			if (v[x][y] == '.') {
				v[x][y] = who;
				q.push (nxt);
			} else if (v[x][y] != who) {
				v[x][y] = '*';
			}
		}
	}
}

int main () {

	ios :: sync_with_stdio (false);
	cin.tie (0);

	int o;
	cin >> o;

	bool flag = false;

	while (o--) {
		if (flag) printf ("\n");
		flag = true;
		
		cin >> n >> m;

		st.clear();

		for (int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			for (int j = 0; j < m; ++j) {
				v[i][j] = s[j];
				if ('a' <= s[j] && s[j] <= 'z')
					st.push_back (make_pair (i, j));
			}
		}

		bfs();

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				printf ("%c", v[i][j]);
			printf ("\n");
		}


	}

	return 0;
}