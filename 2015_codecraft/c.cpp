#include <bits/stdc++.h>
using namespace std;

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	int o;
	cin >> o;

	while (o--) {
		int n, p;
		string s;
		cin >> n >> s >> p;

		if (s[0] == 'o')
			cout << p * 2 << '\n';
		else
			cout << (p * 2) - 1 << '\n';
	}

	return 0;
}