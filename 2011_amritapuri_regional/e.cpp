#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int pr[MAXN];
vector <int> v;

bool check (int x) {
	set <int> s;
	while (x != 1) {
		s.insert (pr[x]);
		x = x / pr[x];
	}

	return s.size() >= 3;
}

void sieve () {
	memset (pr, 0, sizeof pr);
	pr[1] = 1;
	for (long long i = 2; i < MAXN; ++i) {
		if (!pr[i]) {
			pr[i] = i;
			for (long long j = i * i; j < MAXN; j += i)
				pr[j] = i;
		} else if (check (i))
			v.push_back (i);
	}
}

int main () {

	int o;
	cin >> o;

	sieve ();

	for (int i = 0; i < o; ++i) {
		int a;
		scanf ("%d", &a);
		printf ("%d\n", v[a - 1]);
	}

	return 0;
}