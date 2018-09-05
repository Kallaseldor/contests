#include <bits/stdc++.h>
using namespace std;

int pos;
int star;
int wins;

int v[30];

void st(int l, int r, int s) {
	for (int i = l; i >= r; --i)
		v[i] = s;
}

void win() {
	wins++;
	star++;

	if (pos >= 6 && wins >= 3) star++;
	if (star > v[pos]) {
		star -= v[pos];
		pos--;
	}

	if (pos == 0) printf("Legend\n");
}

void lose() {
	wins = 0;

	if (pos <= 20) star--;

	if (star == -1 && pos < 20) {
		pos++;
		star = v[pos] - 1;
	}

	if (star == -1) star = 0;
}

int main() {

	string s;
	cin >> s;

	pos = 25;
	star = 0;

	st(25, 21, 2);
	st(20, 16, 3);
	st(15, 11, 4);
	st(10, 1, 5);

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == 'W') win();
		else lose();

		if (pos == 0) return 0;
	}

	cout << pos << endl;


	return 0;
}