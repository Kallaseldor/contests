#include <bits/stdc++.h>
using namespace std;

pair<int, int> v[1123];
set<pair<int, int> > s;

int main() {

	int n;
	cin >> n;

	if (n == 1 || n == 2 || n == 3) {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &v[i].first, &v[i].second);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			s.insert(make_pair((v[i].first + v[j].first), v[i].second + v[j].second));
		}
	}

	if (s.size() != (n * (n - 1)) / 2) {
		cout << 1 << endl;
	} else {
		cout << 2 << endl;
	}

	return 0;
}