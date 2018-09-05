#include <bits/stdc++.h>
using namespace std;

int main() {

	int a, b;
	cin >> a >> b;

	b %= 360;
	a %= 360;

	b -= a;

	if (b > 180) b -= 360;
	else if (b <= -180) b += 360;

	cout << b << endl;

	return 0;
}