#include <bits/stdc++.h>
using namespace std;

int main () {

	int w = 0;


	for (int i = 0; true; ++i) {
		int a;
		if (w + w >= i) {
			printf ("1 ");
			fflush (stdout);
			cin >> a;
			if (a == 1) ++w;
		} else {
			printf ("2 ");
			fflush (stdout);
			cin >> a;
			if (a == 0) ++w;
		}

		if (a == -1) break;
	}

	return 0;
}