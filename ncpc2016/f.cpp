#include <bits/stdc++.h>
using namespace std;

long double n, p;	//Premios, Pessoas

long double calc(long double q) {
	// cout << "Test: " << q << endl;

	if (q <= 0.5) return 0.0;
	long double c0, c1;
	c0 = 1.0;
	c1 = 0.0;

	for (long double i = 0.0; i < n; i += 1.0) {
		long double temp0, temp1, temp2;
		temp0 = c0 * ((p - i) / (p  + q - i));
		temp1 = c1 * ((p - i + 1.0) / (p + q - i)) + c0 * (q / (p + q - i));
		
		c0 = temp0;
		c1 = temp1;
	}

	return c1;
}

int solve() {

	int l = 1;
	int r = 10 * p;
	int maxindex = -1;
	long double maxp = 0.0;

	while (l <= r) {
		int mid = (l + r) >> 1;

		long double vl = calc((long double) mid);
		long double vr = calc((long double) (mid + 1));

		if (vl + 1e9 > vr) {
			if (maxp < vl) {
				maxp = vl;
				maxindex = mid;
			}
			r = mid - 1;
		} else {
			if (maxp < vr) {
				maxp = vr;
				maxindex = mid;
			}
			l = mid + 1;
		}
	}

	return maxindex;
}

long double mmax(long double a, long double b) {
	return (a > b) ? a : b;
}

int main() {
	cin >> p >> n;

	int pivot = solve();

	long double ans = calc(pivot);

	for (int i = -20; i < 21; ++i) {
		ans = mmax(ans, calc(pivot + i));
	}

	printf("%.12Lf\n", ans);
	return 0;
}