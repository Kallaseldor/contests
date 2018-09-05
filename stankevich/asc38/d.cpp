#include <bits/stdc++.h>
using namespace std;

const double pi = acos (-1);

class Point {
public:
	double x, y;

	Point () {x = 0.0; y = 0.0;}
	Point (double _x, double _y) {
		x = _x; y = _y;
	}

	Point operator+ (const Point & other) const {
		return Point (x + other.x, y + other.y);
	}

	Point operator- (const Point & other) const {
		return Point (x - other.x, y - other.y);
	}

	Point operator * (const Point & other) const {
		return Point (x * other.x - y * other.y, x * other.y + y * other.x);
	}

	double operator~ () const {
		return sqrt (x * x + y * y);
	}

	void print () { printf ("(%.3lf %.3lf)\n", x, y); }
};

class FFT {
public:
	vector <Point> data;
	vector <Point> roots;
	vector <int> rev;
	int s, n;

	void setSize (int ns) {
		s = ns;
		n = (1 << s);

		rev = vector <int> (n);
		data = vector <Point> (n);
		roots = vector <Point> (n + 1);

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < s; ++j)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s - j - 1));

		roots[0] = Point (1, 0);
		Point mult = Point (cos (2 * pi / n), sin (2 * pi / n));
		for (int i = 1; i <= n; ++i)
			roots[i] = roots[i - 1] * mult;
	}

	void bitReverse (vector <Point> & v) {
		vector <Point> temp (n);
		for (int i = 0; i < n; ++i)
			temp[i] = v[rev[i]];
		for (int i = 0; i < n; ++i)
			v[i] = temp[i];
	}

	void transform (bool inverse = false) {
		bitReverse (data);

		for (int i = 1; i <= s; ++i) {
			int m = (1 << i), md2 = m >> 1;
			int start = 0, increment = (1 << (s - i));
			if (inverse) {
				start = n;
				increment *= -1;
			}

			Point t;
			for (int k = 0; k < n; k += m) {
				int index = start;
				for (int j = k; j < md2 + k; ++j) {
					t = roots[index] * data[j + md2];
					index += increment;
					data[j + md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}

		if (inverse)
			for (int i = 0; i < n; ++i) {
				data[i].x /= n;
				data[i].y /= n;
			}
	}

	static vector <int> convolution (const vector <int> & a, const vector <int> & b) {
		int alen = a.size(), blen = b.size();
		int resn = alen + blen - 1;

		int s = 0;
		while ((1 << s) < resn) ++s;
		int n = 1 << s;

		FFT pga, pgb;
		pga.setSize (s);
		for (int i = 0; i < alen; ++i) pga.data[i] = Point (a[i], 0);
		for (int i = alen; i < n; ++i) pga.data[i] = Point (0, 0);
		pga.transform();

		pgb.setSize (s);
		for (int i = 0; i < blen; ++i) pgb.data[i] = Point (b[i], 0);
		for (int i = blen; i < n; ++i) pgb.data[i] = Point (0, 0);
		pgb.transform();

		// for (int i = 0; i < pgb.data.size(); ++i)
		// 	cout << pgb.data[i].x << " " << pgb.data[i].y << endl;

		for (int i = 0; i < n; ++i) pga.data[i] = pga.data[i] * pgb.data[i];
		pga.transform (true);
		vector <int> result = vector <int> (resn);
		for (int i = 0; i < resn; ++i) result[i] = (int) (pga.data[i].x + 0.5);
		
		int actualSize = resn - 1;
		while (actualSize >= 0 && result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize (actualSize + 1);
		return result;
	}
};

int main () {
	
	string s;
	cin >> s;

	vector <int> v;

	for (int i = 0; i < s.size(); ++i) v.push_back (s[i] - '0');

	vector <int> t = FFT :: convolution (v, v);

	long long ans = 0;
	for (int i = 0; i < t.size(); i += 2) {
		long long val = t[i];
		if (v[i >> 1]) ans += (val - 1) >> 1;
	}

	cout << ans << endl;

	return 0;
}