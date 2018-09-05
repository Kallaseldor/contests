#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x, y;

	Point () {}
	Point (int _x, int _y) {
		x = _x; y = _y;
	}
};

struct Circle {
	Point o;
	int r;

	Circle () {}
	Circle (int _x, int _y, int _r) {
		o = Point (_x, _y); r = _r;
	}

	Circle (Point _o, int _r) {
		o = _o; r = _r;
	}

	bool contains (const Point p) {
		if (o.x - r <= p.x && o.x + r >= p.x && o.y - r <= p.y && )
	}
}

int main () {



	return 0;
}