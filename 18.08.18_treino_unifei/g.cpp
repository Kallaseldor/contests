#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const int MAXN = 11234;

struct node {
	double l, r;
	node () {}
	node (double _l, double _r) {
		l = _l; r = _r;
	}

	bool operator < (const node other) {
		if (l != other.l) return l < other.l;
		return r < other.r;
	}
};

node v[MAXN];

int main () {

	int n;
	double x, y;

	while (scanf ("%d %lf %lf", &n, &x, &y) != EOF) {
		y /= 2.0;
		
		for (int i = 0; i < n; ++i) {
			double p, r;
			scanf ("%lf %lf", &p, &r);

			if (r < y - EPS) {
				--i;
				--n;
				continue;
			}

			r = sqrt (r * r - y * y);
			v[i] = node (p - r, p + r);
		}

		sort (v, v + n);

		double l = 0;
		double r = 0;

		int index = 0;
		int ans = 0;

		while (true) {
			++ans;
			while (index < n && v[index].l <= l + EPS) {
				r = max (r, v[index].r);
				++index;
			}

			if (l == r) {
				ans = -1;
				break;
			}

			if (r >= x - EPS) break;
			l = r;
		}

		printf ("%d\n", ans);
	}

	return 0;
}