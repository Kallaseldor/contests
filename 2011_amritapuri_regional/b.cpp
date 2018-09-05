#include <bits/stdc++.h>
using namespace std;

bitset <212> v[212];

struct Point {
	int x, y;

	Point () {}
	Point (int _x, int _y) {
		x = _x; y = _y;
	}

	Point operator+ (const Point & other) const {
		return Point (x + other.x, y + other.y);
	}

	Point operator- (const Point & other) const {
		return Point (x - other.x, y - other.y);
	}

	int operator^ (const Point & other) const {
		return x * other.y - y * other.x;
	}

	int operator* (const Point & other) const {
		return x * other.x + y * other.y;
	}

	int operator~ () const {
		return x * x + y * y;
	}

	int distanceToSegment2 (const Point s1, const Point s2) const {
		Point c = *this;
		if ( 	((s2 - s1) * (c - s1)) <= 0.0 ||
				((s1 - s2) * (c - s2)) <= 0.0) {
			return min(~(s1 - c), ~(s2 - c));
		} else {
			int area = (s2 - s1) ^ (c - s1);
			return (area * area) / (~(s2 - s1));
		}
	}
};

Point p[3];

int getArea (const Point o) {
	int ans = 0;
	ans += abs ((p[0] - o) ^ (p[1] - o));
	ans += abs ((p[1] - o) ^ (p[2] - o));
	ans += abs ((p[2] - o) ^ (p[0] - o));

	return ans;
}

int main () {

	int o;
	cin >> o;

	while (o--) {
		int n;
		scanf ("%d", &n);

		for (int i = 0; i < 212; ++i) v[i].reset();

		int ans = 0;

		while (n--) {
			char op;
			scanf (" %c", &op);

			if (op == 'C') {
				int x, y, r;
				scanf ("%d %d %d", &x, &y, &r);
				x += 100; y += 100;

				for (int i = x - r; i <= x + r; ++i)
					for (int j = y - r; j <= y + r; ++j)
						if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
							if (!v[i][j]) {
								v[i][j] = true;
								++ans;
							}
			} else if (op == 'S') {
				int x, y, l;
				scanf ("%d %d %d", &x, &y, &l);
				x += 100; y += 100;

				for (int i = x; i <= x + l; ++i)
					for (int j = y; j <= y + l; ++j)
						if (!v[i][j]) {
							v[i][j] = true;
							++ans;
						}
			} else if (op == 'T') {
				for (int i = 0; i < 3; ++i)
					scanf ("%d %d", &p[i].x, &p[i].y);

				for (int i = 0; i < 3; ++i) {
					p[i].x += 100;
					p[i].y += 100;
				}
				
				int minx = p[0].x, maxx = p[0].x, miny = p[0].y, maxy = p[0].y;
				for (int i = 0; i < 3; ++i) {
					minx = min (minx, p[i].x);
					maxx = max (maxx, p[i].x);
					miny = min (miny, p[i].y);
					maxy = max (maxy, p[i].y);
				}

				int area = getArea (p[0]);

				for (int i = minx; i <= maxx; ++i)
					for (int j = miny; j <= maxy; ++j)
						if (getArea (Point (i, j)) == area)
							if (!v[i][j]) {
								v[i][j] = true;
								++ans;
							}
			}
		}

		printf ("%d\n", ans);
	}

	return 0;
}