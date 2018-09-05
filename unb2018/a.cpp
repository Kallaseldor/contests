#include <bits/stdc++.h>
using namespace std;

long long v[112345];
unordered_map <long long, int> m;

int main () {

	long long n, k;
	cin >> n >> k;

	for (long long i = 0; i < n; ++i) {
		scanf ("%lld", v + i);
		m[v[i]] = i;
	}

	for (int i = 0; i < n; ++i) {
		long long a = v[i];
		if (m.count (- k + a) && m[- k + a] != i) {
			cout << "Sim" << endl;
			printf ("%d %d\n", i + 1, m[- k + a] + 1);
			return 0;
		}
	}

	cout << "Nao" << endl;

	return 0;
}