#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123456;

int v[MAXN];
int tr[40];

int solve (int x) {
	for (int i = 0; i < 32; ++i) {
		if ((1 << i) >= x) return tr[i + 1];
	}

	return 0;
}

int main () {

	int n;
	cin >> n;

	int lst = 0;

	for (int i = 0; i < n; ++i) scanf ("%d", v + i);

	memset (tr, -1, sizeof tr);
	tr[1] = 28;
	tr[2] = 14;
	tr[3] = 9;
	tr[4] = 7;
	tr[5] = 5;
	tr[9] = 3;
	tr[14] = 2;
	tr[28] = 1;


	vector <int> dn;
	dn.push_back (1);
	dn.push_back (2);
	dn.push_back (3);
	dn.push_back (5);
	dn.push_back (9);
	dn.push_back (14);
	dn.push_back (28);

	for (int i = 27; i > 1; --i)
		if (tr[i] == -1) tr[i] = tr[i + 1];

	int hi = 0;
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		ans += 4;
		hi = 0;

		// cout << i << endl;

		for (int j = i; j < n; ++j) {
			int lst = hi;
			hi = max (hi, v[j]);
			int poss = solve (hi);
			// cout << i << " " << j << " " << poss << endl;
			if (j - i + 1 > poss) {
				int q = 0;
				for (int k = 0; k < dn.size(); ++k) {
					if (dn[k] > j - i) break;
					q = dn[k];
				}
				// Corte a partir de i
				i = i + q - 1;
				break;
			}

			if (j == n - 1) i = j;
		}
	}

	cout << "Total bytes: " << ans << endl;
	

	return 0;
}