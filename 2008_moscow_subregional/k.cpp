#include <bits/stdc++.h>
using namespace std;

int memo[312][312];
vector<int> v;

int solve(int l, int r) {
	if (l == r) return 0;
	if (l + 1 == r) return (v[l] != v[r]);

	int & p = memo[l][r];
	if (p != -1) return p;

	p = 500;
	if (v[l] == v[r]) p = solve(l + 1, r - 1) + 1;

	if (v[l] == v[r]) {
		for (int i = l + 1; i < r; ++i) {
			if (v[i] == v[l])
				p = min(p, solve(l, i) + solve(i, r));
		}
	}

	return p;
}

int main() {

	memset(memo, -1, sizeof memo);

	int n, k;
	cin >> n >> k;

	int a;
	scanf("%d", &a);
	v.push_back(a);

	for (int i = 1; i < n; ++i) {
		scanf("%d", &a);
		if (a != v[v.size() - 1]) v.push_back(a);
	}

	n = v.size();

	cout << solve(0, n - 1) << endl;

	return 0;
}