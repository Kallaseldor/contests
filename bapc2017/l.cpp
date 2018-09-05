#include <bits/stdc++.h>
using namespace std;

string s, t;
unordered_map <string, long double> m;
unordered_map <string, bool> vis;

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	int n;
	cin >> n;

	m["pink"] = 0.0;
	vis["pink"] = true;

	long double d;

	for (int i = 0; i < n; ++i) {
		cin >> s >> t >> d;
		d = log2 (d);
		m[s] = max (m[s], m[t] + d);
		vis[s] |= vis[t];
	}

	if (vis["blue"])
		if (m["blue"] >= 4.0 ) {
			cout << fixed << setprecision (20) << 10.0 << endl;
		} else {
			m["blue"] = pow (2, m["blue"]);
			cout << fixed << setprecision (20) << min (m["blue"], 10.0L) << endl;
		}
	else
		cout << fixed << setprecision (20) << 0.0 << endl;

	return 0;
}