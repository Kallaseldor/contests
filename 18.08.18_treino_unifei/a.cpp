#include <bits/stdc++.h>
using namespace std;

set <int> s;

int main () {

	int n;
	while (cin >> n) {
		if (n == 0) break;

		s.clear();
		int lst = 0x3F3F3F3F;

		for (int i = 0; i < n; ++i) {
			int a;
			scanf ("%d", &a);
			if (lst != 0x3F3F3F3F)
				s.insert (abs (a - lst));

			lst = a;
		}

		if (s.size() == n - 1 && *s.begin() == 1 && *s.rbegin() == n - 1) cout << "SIM\n";
		else cout << "NAO\n";
	}

	return 0;
}