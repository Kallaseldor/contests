#include <bits/stdc++.h>
using namespace std;

const int MAXN = 512345;

int st[MAXN];

int t[MAXN];
int v[MAXN];

int main () {

	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		scanf ("%d", st + i);
		if (st[i])
			scanf ("%d", v + i);
	}

	t[0] = 0;
	for (int i = 1; i <= n; ++i) {
		t[i] = st[i] ^ st[i - 1];
	}

	for (int i = 1; i <= n; ++i)
		if (st[i]) {
			t[v[i]] ^= 1;
			t[i + 1] ^= 1;
		}

	int ans = 0;
	int curr = 0;
	for (int i = 1; i <= n; ++i) {
		curr ^= t[i];
		if (curr) ans++;
	}

	cout << ans << endl;

	return 0;
}