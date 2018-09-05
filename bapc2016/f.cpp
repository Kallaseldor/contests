#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
	point () {}
	point (const double _x, const double _y) {
		x = _x;
		y = _y;
	}

	bool operator < (const point & p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}

	bool operator == (const point & p) const {
		if (x != p.x) return false;
		if (y != p.y) return false;
		return true;
	}

	double operator ^ (const point & p) const {
		return x * p.y - y * p.x;
	}

	double operator * (const point & p) const {
		return x * p.x + y * p.y;
	}

	point operator - (const point & p) const {
		return point (x - p.x, y - p.y);
	}

	friend ostream & operator << (ostream & os, const point & p) {
		os << "(" << p.x << ", " << p.y << ")";
		return os;
	}
};

struct line {
	double a, b, c;
	line () {}
	line (const double _a, const double _b, const double _c) {
		a = _a; b = _b; c = _c;
	}
	line (point p, point q) {
		// cout << p << " " << q << endl;
		a = p.y - q.y;
		b = q.x - p.x;
		c = p.x * q.y - p.y * q.x;
		// cout << a << " " << b << " " << c << endl << endl;
	}

	bool isparallel (const line & other) const {
		return a * other.b == b * other.a;
	}

	point intersect (const line & p) const {
		double d = a * p.b - b * p.a;
		double x = -c * p.b + b * p.c;
		double y = -a * p.c + c * p.a;

		return point (x / d, y / d);
	}

	bool contains (const point & p) const {
		cout << a << " " << b << " " << c << " -> " << p.x << " " << p.y << endl;
		if (a * p.x + b * p.y + c == 0) return true;
		return false;
	}
};

struct intersection {
	point p;
	int x, y;

	intersection () {}
	intersection (point _p, int _x, int _y) {
		p = _p;
		x = _x;
		y = _y;
	}

	int get (const int o) const {
		return (x == o) ? y : x;
	}

	bool operator < (const intersection & other) const {
		return p < other.p;
	}
};

struct street {
	string s;
	int id;
	line r;

	point dir;

	vector <intersection> other;

	street () {}
	street (string _s, int _id, point _p, point _q) {
		s = _s;
		id = _id;
		r = line (_p, _q);

		dir = _p - _q;
		if (dir.x < 0 || (dir.x == 0 && dir.y < 0)) {
			dir.x *= -1;
			dir.y *= -1;
		}
	}

	intersection operator [] (const int i) {
		return other[i];
	}

	int size () {
		return other.size();
	}

	bool isparallel (const street & s) {
		return r.isparallel (s.r);
	}

};

vector <street> v;
int startindex;
point start;

bool vis[112];

point pivot;

vector <int> order;

int main () {

	ios :: sync_with_stdio (false); cin.tie (0); cout.tie (0);

	int n;
	long long k;

	int sx, sy;

	cin >> n >> k >> sx >> sy;

	start = point (sx, sy);
	pivot = point (1.0, 0.0);

	for (int i = 0; i < n; ++i) {
		string s;
		double x1, y1, x2, y2;
		cin >> s >> x1 >> y1 >> x2 >> y2;

		v.push_back (street (s, v.size(), point (x1, y1), point (x2, y2)));
	}

	int index = -1;

	for (int i = 0; i < n; ++i) {
		cout << endl << "Check em " << i << endl;
		if (v[i].r.contains (start)) 
			index = i;

		for (int j = 0; j < n; ++j)
			if (!v[i].isparallel(v[j]))
				v[i].other.push_back (intersection (v[i].r.intersect (v[j].r), i, j));
		sort (v[i].other.begin(), v[i].other.end());

		cout << "O tamanho do " << i << " eh " << v[i].size() << endl;
	}

	startindex = index;

	point dir = v[index].dir;
	memset (vis, false, sizeof vis);
	long long cyclesize = 0;

	while (!vis[index] && k) {
		--k;
		++cyclesize;
		order.push_back (index);

		int nxt = -1;

		if (index == startindex) {
			for (int i = 0; i < v[index].size(); ++i) {
				cout << "To testando " << v[index][i].p << " e " << start << endl;
				if (start < v[index][i].p || v[index][i].p == start) {
					cout << "Meu next eh " << v[index][i].get (index) << endl;
					return 0;
				}
			}

			cout << "Nao achei" << endl;
			return 0;

			continue;
		}

		for (int i = 0; i < v[index].size(); ++i) {
		
		}
	}

	if (k) {

	} else {
		cout << v[index].s << endl;
	}

	return 0;
}