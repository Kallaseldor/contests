#include <bits/stdc++.h>
using namespace std;

#define INF 0x3F3F3F3F

int memo[112][112][112];
int v[112];
int m, n;

int solve(int pos, int w1, int w2) {
	if (w1 < 0 || w2 < 0) return -INF;
	if (pos == n) return 0;

	int &p = memo[pos][w1][w2];
	if (p != -1) return p;

	p = max(1 + solve(pos + 1, w1 - v[pos], w2), 1 + solve(pos + 1, w1, w2 - v[pos]));
	p = max(p, solve(pos + 1, w1, w2));

	return p;
}

vector<int> a1, a2;
void buildAns(int pos, int w1, int w2) {
	int p = solve(pos, w1, w2);
	if (p == 0) {
		return;
	}

	if (p == 1 + solve(pos + 1, w1 - v[pos], w2)) {
		a1.push_back(pos + 1);
		buildAns(pos + 1, w1 - v[pos], w2);
	} else if (p == 1 + solve(pos + 1, w1, w2 - v[pos])) {
		a2.push_back(pos + 1);
		buildAns(pos + 1, w1, w2 - v[pos]);
	} else {
		buildAns(pos + 1, w1, w2);
	}
}

int main() {

	cin >> m >> n;
	memset(memo, -1, sizeof memo);

	for (int i = 0; i < n; ++i) scanf("%d", v + i);
	
	cout << solve(0, m, m) << endl;

	buildAns(0, m, m);

	printf("Lado A:");
	for (int i = 0; i < a1.size(); ++i) printf(" %d", a1[i]);
	printf("\nLado B:");
	for (int i = 0; i < a2.size(); ++i) printf(" %d", a2[i]);
	printf("\n");

	return 0;
}