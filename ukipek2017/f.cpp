#include <bits/stdc++.h>
using namespace std;

double memo[412][412];

double solve(int n, int k) {
	if (k == 0) return 0.0;
	if (n == 0) return -solve(1, k);

	double &p = memo[n][k];
	if (p != -1.0) return p;

	p = (1.0 + solve(n - 1, k - 1)) * 0.5 + (solve(n, k - 1)) * 0.5;
	return p;
}

int main() {

	int n, k;
	cin >> n >> k;

	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= k; ++j)
			memo[i][j] = -1.0;

	printf("%.12lf\n", solve(n, k));

	return 0;
}