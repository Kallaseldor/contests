#include <bits/stdc++.h>
using namespace std;

string s;
string t;
long long memo[112345][3];

long long solve (int i, int j) {
	if (j == 3) return 1;
	if (i == s.size()) return 0;

	long long & p = memo[i][j];
	if (p + 1) return p;

	p = solve (i + 1, j);
	if (s[i] == t[j]) 
		p += solve (i + 1, j + 1);

	return p;
}

int main () {

	int n;
	cin >> n;

	t = "LOL";

	for (int i = 0; i < n; ++i) {
		cin >> s;
		memset (memo, -1, sizeof memo);

		cout << solve (0, 0) << endl;
	}

	return 0;
}