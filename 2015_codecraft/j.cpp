#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int p, q, r;

int a[MAXN];
int b[MAXN];
int c[MAXN];

long long temp[MAXN];

long long solve () {

	int k = 0;
	for (int j = 0; j < q; ++j) {
		while (k < r && (c[k] < b[j] || k < j)) ++k;
		temp[j] = r - k;
	}

	for (int j = q - 2; j >= 0; --j)
		temp[j] += temp[j + 1];

	long long ans = 0;
	int j = 0;
	for (int i = 0; i < p; ++i) {
		while (j < q && (b[j] < a[i] || j < i)) ++j;
		ans += temp[j];
	}

	return ans;
}

int main () {

	int o;
	cin >> o;

	while (o--) {

		cin >> p;
		for (int i = 0; i < p; ++i) scanf ("%d", a + i);
		
		cin >> q;
		for (int j = 0; j < q; ++j) scanf ("%d", b + j);
		
		cin >> r;
		for (int k = 0; k < r; ++k) scanf ("%d", c + k);

		cout << solve() << endl;
	}

	return 0;
}