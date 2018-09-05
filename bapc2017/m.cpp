#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

int inv = 1;

struct Point {
	int x, y;
	Point () {
		x = 0; y = 0;
	}
	Point (int _x, int _y) {
		x = _x; y = _y;
	}

	bool operator < (const Point & p) const {
		if (x != p.x) return x < p.x;
		return y * inv < p.y;
	}
};

vector <Point> v;
map <int, int> numsx;
map <int, int> numsy;

int main () {

	int n;
	cin >> n;

	Point init, dest;
	scanf ("%d %d %d %d", &init.x, &init.y, &dest.x, &dest.y);

	if (dest.x < init.x) swap (dest, init);
	if (dest.y < init.y) inv = -1;

	numsx[init.x] = 1;
	numsy[init.y] = 1;
	numsx[dest.x] = 1;
	numsy[dest.y] = 1;

	v.push_back (init);
	v.push_back ()
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf ("%d %d", &x, &y);
		if (x < init.x && x < dest.x) continue;
		if (x > init.x && x > dest.x) continue;
		if (y < init.y && y < dest.y) continue;
		if (y > init.y && y > dest.y) continue;
		v.push_back (Point (x, y));
		numsx[x] = 1;
		numsy[y] = 1;
	}

	int index = 0;
	for (map <int, int> :: iterator it = numsx.begin(); it != numsx.end(); ++it)
		it -> second = index++;

	index = 0;
	for (map <int, int> :: iterator it = numsy.begin(); it != numsy.end(); ++it)
		it -> second = index++;

	init.x = numsx[init.x];
	init.y = numsy[init.y];
	dest.x = numsx[dest.x];
	dest.y = numsy[dest.y];

	for (int i = 0; i < v.size(); ++i) {
		v[i].x = numsx[v[i].x];
		v[i].y = numsy[v[i].y];
	}

	sort (v.begin(), v.end());

	int tt = numsy.size();

	for (int i = v.size() - 1; i >= 0; --i) {
		if (inv == 1) {
			update (1, 0, tt, v[i].y, query (1, 0, tt, min (v[i].y, dest.y), max (v[i].y, dest.y)) + 1);
		} else {
			update (1, 0, tt, v[i].y, query (1, 0, tt, min (v[i].y, dest.y), max (v[i].y, dest.y)) + 1);
		}
	}

	if (inv == 1) printf ("%d\n", query (1, 0, tt, init.y, dest.y));
	else printf ("%d\n", query (1, 0, tt, dest.y, init.y));

	return 0;
}