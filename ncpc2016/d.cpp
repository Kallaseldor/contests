#include <bits/stdc++.h>
using namespace std;

long long mmax(long long a, long long b) {
	return (a > b) ? a : b;
}

int main() {

	int n;
	cin >> n;

	long long stocks = 0;
	long long money = 100;
	long long maxmoney = 100;

	long long v[n];
	for (int i = 0; i < n; ++i) scanf("%lld", v + i);

	for (int i = 0; i < n - 1; ++i) {
		if (v[i] > v[i + 1]) {
			money += stocks * v[i];
			stocks = 0;
		} else if (v[i] < v[i + 1]) {
			long long q = money / v[i];

			if (stocks + q > 100000LL) {
				q = 100000LL - stocks;
			}

			money -= q * v[i];
			stocks += q;
		}

		maxmoney = mmax(money, maxmoney);
	}

	money += stocks * v[n - 1];
	maxmoney = mmax(money, maxmoney);

	cout << maxmoney << endl;

	return 0;
}