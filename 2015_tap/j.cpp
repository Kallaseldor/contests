#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int v[MAXN];

int main () {

	int n;
	while (scanf ("%d", &n) != EOF) {

		for (int i = 0; i < n; ++i) scanf ("%d", v + i);
		sort (v, v + n);

		int cnt = 1;
		int target = v[0] % (n + 1);

		if (target == 0) {
			printf ("S\n");
			continue;
		}

		v[0] -= target;
		bool flag = true;
		for (int i = 1; i < n; ++i) {
			if (cnt == target) ++cnt;
			v[i] -= (cnt++);
			if (v[i] < v[0]) {
				flag = false;
				break;
			}
		}

		if (!flag) printf ("S\n");
		else printf ("N\n");
	}

	return 0;
}