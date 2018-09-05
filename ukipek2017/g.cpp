#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y, z;
	point() {}
	point (int a, int b, int c) {
		x = a; y = b; z = c;
	}

	bool operator!= (const point p) const {
		if (x == p.x && y == p.y && z == p.z) return false;
		return true;
	}

	bool operator== (const point p) const {
		if (x == p.x && y == p.y && z == p.z) return true;
		return false;
	}

	void prnt() {
		printf("(%d %d %d)", x, y, z);
	}
};

struct path {
	vector<point> v;

	point get(int x) {
		if (v.size() > x) return v[x];
		else return v[v.size() - 1];
	}

	void put(point p) {
		v.push_back(p);
	}

	point curr() {
		return v[v.size() - 1];
	}

	void clr() {
		while (!v.empty()) v.pop_back();
	}

};

path p1, p2;
point e1, e2;

int quant;

int go(int a, int b) {
	if (a > b) return -1;
	else return 1;
}

void findPath1() {
	point curr = p1.get(0);
	// cout << "Teste: " << endl;
	// curr.prnt();
	// cout << endl;
	// e1.prnt();
	// cout << endl << endl << endl;

	// cout << "!!!! " << (curr != e1) << endl;
	while (curr != e1) {
		if (curr.x != e1.x) curr.x += go(curr.x, e1.x);
		else if (curr.y != e1.y) curr.y += go(curr.y, e1.y);
		else if (curr.z != e1.z) curr.z += go(curr.z, e1.z);

		p1.put(curr);
	}

	return;
}

path temp;
void randMov(point curr, int q) {
	if (q == 0) return;
	if (curr == e2) {
		quant = 5 - q;
		return;
	}
	int c = rand() % 6;
	
	if (c < 2) curr.x += (c == 0) ? -1 : 1;
	else if (c < 4) curr.y += (c == 2) ? -1 : 1;
	else curr.z += (c == 4) ? -1 : 1;

	temp.put(curr);
	randMov(curr, q - 1);

	return;
}

void findPath2() {
	point curr = p2.get(0);

	int index = 0;

	while (curr != e2) {
		index++;
		point nxt = curr;
		/*cout << "Antes:" << endl;
		nxt.prnt();
		cout << endl;
		*/

		if (nxt.x != e2.x) nxt.x += go(nxt.x, e2.x);
		else if (nxt.y != e2.y) nxt.y += go(nxt.y, e2.y);
		else if (nxt.z != e2.z) nxt.z += go(nxt.z, e2.z);


		/*cout << "Depois:" << endl;
		nxt.prnt();
		cout << endl << endl << endl;
		*/
		
		if (nxt == p1.get(index - 1) || nxt == p1.get(index)) {
			bool flag = true;
			while (flag) {

				flag = false;

				temp.clr();
				quant = 5;
				randMov(curr, 5);
				for (int i = 0; i < quant; ++i) {
					if (temp.get(i) == p1.get(i + index) || temp.get(i) == p1.get(i + index - 1)) {flag = true; break;}
				}
			}
			index += quant - 1;
			for (int i = 0; i < quant; ++i) {
				p2.put(temp.get(i));
			}

			curr = temp.get(100000);

		} else {
			p2.put(nxt);
			curr = nxt;
		}

	}

	return;

}

void printAns() {
	int tam = max(p1.v.size(), p2.v.size());

	for (int i = 0; i < tam; ++i) {
		p1.get(i).prnt();
		printf(" ");
		p2.get(i).prnt();
		printf("\n");
	}
}

int main() {

	srand(time(NULL));

	point s1, s2;

	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;

	e1 = point(d, e, f);
	s1 = point(a, b, c);

	cin >> a >> b >> c >> d >> e >> f;

	e2 = point(d, e, f);
	s2 = point(a, b, c);

	p1.put(s1);
	p2.put(s2);

	findPath1();
	findPath2();

	printAns();

	//cout << p1.v.size() << endl;
	
	return 0;
}