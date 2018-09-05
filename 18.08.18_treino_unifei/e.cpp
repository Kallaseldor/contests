#include <bits/stdc++.h>
using namespace std;

int main () {


	long long n1, d1, n2, d2;
	cin >> n1;

	while (scanf ("%lld", &n1) != EOF) {
		char c;
		char op;

		scanf (" %c %lld", &c, &d1);
		scanf (" %c %lld %c %lld", &op, &n2, &c, &d2);

		long long n, d;
		
		if (op == '+') {
			n = n1 * d2 + n2 * d1;
			d = d1 * d2;
		} else if (op == '-') {
			n = n1 * d2 - n2 * d1;
			d = d1 * d2;
		} else if (op == '*') {
			n = n1 * n2;
			d = d1 * d2;
		} else {
			n = n1 * d2;
			d = d1 * n2;
		}

		long long g = __gcd (abs (n), abs(d));

		printf ("%lld/%lld = %lld/%lld\n", n, d, n / g, d / g);
	}

	return 0;
}