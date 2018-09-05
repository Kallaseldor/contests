#include <bits/stdc++.h>
using namespace std;

int main () {

	ios :: sync_with_stdio (false);
	cin.tie (0);

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		bool flag = true;
		string s;
		cin >> s;

		for (int j = 0; j < s.size(); ++j)
			if (s[j] == 'D') {
				flag = false;
				break;
			}

		if (flag)
			cout << "Possible\n";
		else
			cout << "You shall not pass!\n";
	}



	return 0;
}