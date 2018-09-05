#include <bits/stdc++.h>
using namespace std;

double a, b, c, d, t, m;

double getVal (double x) {
	return a * x * x * x + b * x * x + c * x + d - (t / m);
}

double bs (double l, double r) {
	while (r - l >= 1e-9) {
		double mid = (r + l) / 2.0;
		if (getVal (mid) >= 0.0)
			r = mid;
		else
			l = mid;
	}

	return r;
}

void prnt (double d) {
	d *= 100.0;
	d = floor (d);
	d /= 100.0;

	printf ("%.2lf\n", d);
}

int main () {

	while (cin >> a >> b >> c >> d >> m >> t)
		prnt (bs (0.0, 1e100));

	return 0;
}