#include <bits/stdc++.h>
using namespace std;

bool mat[512][512];

int vx[4] = {1, 1, -1, -1};
int vy[4] = {1, -1, 1, -1};

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n + 2; ++i)
		for (int j = 0; j < m + 2; ++j)
			mat[i][j] = false;

	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= m; ++j) {
			if (s[j] == 'N') mat[i][j] = true;
			else mat[i][j] = false;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {

			if (!mat[i][j]) continue;

			if ((mat[i + 1][j] || mat[i - 1][j]) && (mat[i][j + 1] || mat[i][j - 1])) {
				cout << "Reorganize o tabuleiro" << endl;
				return 0;
			}

			for (int k = 0; k < 4; ++k) {
				if (mat[i + vx[i]][j + vy[j]]) {
					cout << "Reorganize o tabuleiro" << endl;
					return 0;
				}
			}

		}
	}

	cout << "Comece a partida" << endl;

	return 0;
}