#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAXN = 2123;

struct Point {
	int x, y;
	Point() {}
	Point (int a, int b) {
		x = a; y = b;
	}

	bool operator< (const Point p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

void Add (long long & a, long long b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

long long memo[MAXN];
long long fat[212345];
long long inv[212345];
vector<Point> v;

long long fexp (long long b, long long e) {

	long long ans = 1;
	while (e != 0) {
		if (e & 1LL) ans = (ans * b) % MOD;
		e >>= 1; b = (b * b) % MOD;
	}

	return ans;
}

inline long long calc (int a, int b) {
	long long ans = fat[a + b] * inv[a];
	ans %= MOD;
	ans *= inv[b];

	return ans % MOD;
}

int n, m, k;

int main() {

	int o;
	cin >> o;

	fat[0] = 1;
	fat[1] = 1;
	inv[0] = 1;
	inv[1] = 1;
	for (long long i = 2LL; i < 212345LL; ++i) {
		fat[i] = fat[i - 1] * i;
		fat[i] %= MOD;
		inv[i] = fexp(fat[i], MOD - 2) % MOD;
	}

	while (o--) {

		cin >> n >> m >> k;

		v.clear();

		for (int i = 0; i < k; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			--x; --y;
			v.push_back(Point(x, y));
		}


		v.push_back(Point(n - 1, m - 1));
		
		sort(v.begin(), v.end());

		// DP Iterativa
		for (int i = 0; i <= k; ++i) {
			int x = v[i].x;
			int y = v[i].y;

			long long ans = calc(x, y);
			for (int j = 0; j < i; ++j) {
				if (v[j].y > y) continue;
				ans -= memo[j] * calc(x - v[j].x, y - v[j].y);
				ans %= MOD;
				Add(ans, MOD);
			}

			memo[i] = ans;
		}

		cout << memo[k] % MOD << endl;
	}


	return 0;
}