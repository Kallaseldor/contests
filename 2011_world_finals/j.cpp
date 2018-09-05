#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;
const int MAXN = 1123456;

short int memo[MAXN][400];
int H[MAXN];
int L[MAXN];

vector<int> v;

int main() {
	memset(memo, -1, sizeof memo);

	// Hi - LIM = 144
	H[0] = 0;
	H[1] = 1;
	for (int i = 2; i < 200; ++i) {
		H[i] = H[i - 1] + (i * i);
		v.push_back(H[i]);
	}


	// Lo - LIM = 181
	L[0] = 0;
	L[1] = 1;
	L[2] = 4;
	for (int i = 3; i < 200; ++i) {
		L[i] = L[i - 2] + (i * i);
		v.push_back(L[i]);
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); ++i) {
		memo[0][i] = 0;
	}

	for (int w = 0; w < 1000456; ++w) {
		for (int i = 0; i < 400; ++i) {
			int ans = 100;
			if (w - v[i] >= 0) ans = min(ans, memo[w - v[i]][i - 1] + 1);
			if (i != 0 && ans > memo[w][i - 1]) ans = memo[w][i - 1];
			memo[w][i] = ans;
		}
	}	


	int n;
	int tt = 0;
	while (scanf("%d", &n) != EOF) {
		++tt;
		if (memo[n][v.size() - 1] == 100) {
			printf("Case %d: impossible\n", tt);
			continue;
		}

		cout << memo[n][v.size() - 1] << endl;
	}

	return 0;
}