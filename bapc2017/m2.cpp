#include <bits/stdc++.h>
using namespace std;

vector <pair <int, int> > v;

// If you dont need to reconstruct the sequence
int lis () {
	
	multiset<int> s;
	multiset<int> :: iterator it;

	for (int i = 0; i < v.size(); ++i) {
		s.insert (v[i].second);
		it = s.upper_bound (v[i].second);	// for strictly increasing subsequence:
											// it = s.lower_bound (v[i]); ++it;

		if (it != s.end())
			s.erase (it);
	}

	return s.size();
}

int main () {

	int n;
	cin >> n;
	pair <int, int> init;
	pair <int, int> dest;

	scanf ("%d %d %d %d", &init.first, &init.second, &dest.first, &dest.second);

	int inv = 1;
	if (init.first > dest.first) swap (init, dest);
	if (init.second > dest.second) inv = -1;

	init.second *= inv;
	dest.second *= inv;

	v.push_back (init);
	v.push_back (dest);

	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf ("%d %d", &x, &y);
		y *= inv;

		if (x < init.first && x < dest.first) continue;
		if (x > init.first && x > dest.first) continue;
		if (y < init.second && y < dest.second) continue;
		if (y > init.second && y > dest.second) continue;

		v.push_back (make_pair (x, y));
	}

	sort (v.begin(), v.end());

	cout << lis() - 2 << endl;

	return 0;
}