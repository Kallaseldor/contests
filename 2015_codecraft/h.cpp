#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int n, k;
int v[MAXN];

int st[4 * MAXN];
map <int, int> nums;

void update (int nd, int l, int r, int x, int val) {
	st[nd] += val;
	if (l == r) return;

	int mid = (l + r) >> 1;

	if (x <= mid)
		update ((nd << 1), l, mid, x, val);
	else
		update ((nd << 1) + 1, mid + 1, r, x, val);
}

int query (int nd, int l, int r, int ll, int rr) {
	if (rr < l || r < ll) return 0;
	if (ll <= l && r <= rr) return st[nd];

	int mid = (l + r) >> 1;

	return query ((nd << 1), l, mid, ll, rr) + query ((nd << 1) + 1, mid + 1, r, ll, rr);
}

int main () {

	int n;
	long long k;
	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		scanf ("%d", v + i);
		nums[v[i]] = 1;
	}

	int index = 1;
	for (map <int, int> :: iterator it = nums.begin(); it != nums.end(); ++it)
		it -> second = index++;

	for (int i = 0; i < n; ++i)
		v[i] = nums[v[i]];

	long long inv = 0;
	long long ans = 0;

	int r = 0;
	for (int l = 0; l < n; ++l) {
		while (r <= l || (r < n && inv < k)) {
			inv += query (1, 0, n + 1, v[r] + 1, n + 1);
			update (1, 0, n + 1, v[r], 1);
			++r;
		}

		if (inv >= k) ans += n - r + 1;
		inv -= query (1, 0, n + 1, 0, v[l] - 1);
		update (1, 0, n + 1, v[l], -1);
	}

	cout << ans << endl;

	return 0;
}