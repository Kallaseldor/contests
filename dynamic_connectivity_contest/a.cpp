#include <bits/stdc++.h>
using namespace std;

const int MAXN = 312345;

int pai[MAXN];
stack <pair <int, int> > s;

int get (int x) {
	if (pai[x] == x)
		return x;

	// Save (x, pai[x])
	s.push (make_pair (x, pai[x]));
	pai[x] = get (pai[x]);
	return pai[x];
}

int unite (int x, int y) {
	x = get (x);
	y = get (y);
	s.push (make_pair (x, x));
	pai[x] = y;
}

int rollback (int x) {
	while (s.size() > x) {
		pair <int, int> p = s.top();
		s.pop();

		pai[p.first] = p.second;
	}
}

int main () {



	return 0;
}