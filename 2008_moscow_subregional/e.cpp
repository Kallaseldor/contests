#include <bits/stdc++.h>
using namespace std;

pair<int, pair<int, int> > v[112];
pair<int, int> memo[112][1123];

int n, T;

pair<int, int> solve(int pos, int t) {
	if (pos == n) return make_pair(0, 0);
	if (t > T) return make_pair(-100000, 0);

	pair<int, int> &p = memo[pos][t];
	if (p.first != -1) return p;

	pair<int, int> s1 = solve(pos + 1, t - v[pos].second.first);
	s1.first += v[pos].first;
	s1.second += v[pos].first * (v[pos].second.first + t);

	pair<int, int> s2 = solve(pos + 1, t);

	if (s1.first != s2.first) {
		if (s1.first < s2.first) p = s2;
		else p = s1;
	} else {
		if (s1.first < s2.first) p = s1;
		else p = s2;
	}

	return p;
}

bool cmp (const pair<int, pair<int, int> > a, const pair<int, pair<int, int> > b) {
	return a.second.first * b.first < a.first * b.second.first;
}

void back(int pos, int t) {
	pair<int, int> ans = solve(pos, t);
	if (ans.first == 0) return;

	if (ans.first == solve(pos + 1, t).first) {
		back(pos + 1, t);
	} else {
		printf("%d%c", v[pos].second.second, (solve(pos + 1, t - v[pos].second.first).first == 0) ? '\n' : ' ');
		back(pos + 1, t);
	}
}

int main() {

	cin >> n >> T;

	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &v[i].first, &v[i].second.first);
		v[i].second.second = i + 1;
	}

	sort(v, v + n, cmp);

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= T; ++j) {
			memo[i][j] = make_pair(-1, -1);
		}
	}

	cout << solve(0, 0).first << endl;
	back(0, 0);

	return 0;
}