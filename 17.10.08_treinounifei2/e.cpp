#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000000LL;

int m, n;
long long memo[112][112];
pair<int, int> v[112];

long long solve(int pos, int last) {
	//cout << "@ " << pos << endl;
	if (pos == -1) {
		long long ans = 0;
		for (int i = 0; i < n; ++i) {
			if (v[i].first != 0) break;
			ans += solve(i, -1);
			if (ans > MOD) ans -= MOD;
		}

		return ans;
	}

	if (v[pos].second == m) return 1;
	
	long long &p = memo[pos][last + 1];
	if (p != -1) return p;

	p = 0;
	for (int i = pos + 1; i < n; ++i) {
		//if (v[i].first > v[pos].first && v[i].second > v[pos].second && v[pos].second >= v[i].first && (last == -1 || v[last].second > v[i].first)) {
		if (v[pos].first < v[i].first && v[pos].second >= v[i].first && v[i].second > v[pos].second) {
			if (last == -1 && v[i].second > 0) {
				p += solve(i, pos);
				if (p > MOD) p -= MOD;
			} else if (last != -1 && v[last].second < v[i].first) {
				p += solve(i, pos);
				if (p > MOD) p -= MOD;
			}
		}
	}

	return p;
}

int main() {


	while (1) {
		//cout << "===================================" << endl;
		scanf("%d %d", &m, &n);
		if (n == 0) break;
		for (int i = 0; i < n; ++i) scanf("%d %d", &v[i].first, &v[i].second);

		sort(v, v + n);

		memset(memo, -1, sizeof memo);

		printf("%lld\n", solve(-1, -1));

	}



	return 0;
}