#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123456;
int v[MAXN];

int lst[MAXN];
int gap[MAXN];

int main () {

	int n;
	cin >> n;

	memset (gap, -1, sizeof gap);
	memset (lst, 0, nsizeof lst);

	for (int i = 0; i < n; ++i) scanf ("%d", v + i);

	for (int i = 0; i < n; ++i) {
		int x = v[i];
		gap[x] = max (gap[x], i + 1 - lst[x]);
		lst[x] = i + 1;
	}

	gap[0] = n + 5;
	int ans = 0;
	for (int i = 1; i < MAXN; ++i) {
		if (gap[i] == -1) continue;
		gap[i] = max (gap[i], n - lst[i]);
		if (gap[i] < gap[ans]) ans = i;
	}


	cout << gap[ans] << " " << ans << endl;

	return 0;
}