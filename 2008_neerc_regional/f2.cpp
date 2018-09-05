#include <bits/stdc++.h>
using namespace std;

long long memo1[312];

long long qtdNums (int pos) {
	if (pos == 0) return 0;
	if (pos == 1) return 1;

	long long &p = memo1[pos];
	if (p != -1LL) return p;

	p = qtdNums(pos - 1) + qtdNums(pos - 2);
	return p;
}

int main() {

	long long n;
	cin >> n;

	memset(memo1, -1LL, sizeof memo1);

	if (n <= 3) {
		if (n == 0) cout << 0 << endl;
		if (n == 1) cout << 1 << endl;
		if (n == 2 || n == 3) cout << 2 << endl;
		return 0;
	}

	long long q = 0;
	long long k = 0;
	int siz = 0;

	for (long long i = 0; i < 301; ++i) {
		q += i * qtdNums(i);
		k += qtdNums(i);
		cout << i << " " << q << endl;

		if (q >= n) {
			siz = i;
			k -= qtdNums(i);
			q -= i * qtdNums(i);
			break;
		}
	}

	string last;
	for (int i = siz; i > 0; --i) {
		if (qtdNums(i - 1) < n) {
			last += "1";
			n -= qtdNums(i - 1);
		} else {
			last += "0";
		}
	}

	cout << last << endl;

	return 0;
}