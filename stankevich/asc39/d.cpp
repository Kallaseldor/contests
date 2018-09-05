#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112;
const long long INF = 0x3F3F3F3F3F3F3F3FLL;

int n;
long long v[MAXN];
long long s[MAXN];

long long memo[MAXN][MAXN][MAXN];

long long solve (int l, int r, int fr) {
	if (l > r) return 3 * (fr >> 1);

	long long & p = memo[l][r][fr];
	if (p != INF) return p;

	p = -INF;
	long long op1, op2;

	// Abrir um cara da esquerda
	op1 = s[r] - s[l] + (3LL * fr) - solve (l + 1, r, fr);
	op2 = 4LL + solve (l + 1, r, fr);

	p = max (p, min (op1, op2));


	// Abrir um cara da direita
	op1 = s[r - 1] - s[l - 1] + (3LL * fr) - solve (l, r - 1, fr);
	op2 = 4LL + solve (l, r - 1, fr);

	p = max (p, min (op1, op2));

	// Abrir um 3
	if (fr)
		p = max (p, s[r] - s[l - 1] + (3LL * (fr - 1)) - solve (l, r, fr - 1));

	return p;
}

int main () {

	// freopen ("diamonds.in", "r", stdin);
	// freopen ("diamonds.out", "w", stdout);

	cin >> n;

	int tr = 0;
	long long sum = 0;
	for (int i = 1; i <= n; ++i) {
		scanf ("%lld", v + i);
		sum += v[i];
		if (v[i] == 3) {
			tr++;
			--i;
			--n;
		}
	}

	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j)
			for (int k = 0; k <= n; ++k)
				memo[i][j][k] = INF;

	sort (v, v + n);

	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + v[i];

	cout << solve (1, n, tr) << " " << sum - solve (1, n, tr) << endl;

	return 0;
}