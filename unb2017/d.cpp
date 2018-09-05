#include <bits/stdc++.h>
using namespace std;

int v[212345];
int s[212345];

int main() {

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) scanf("%d", &v[i + 1]);
	s[0] = 0;

	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] + v[i];
	}

	int ans = -21234567;
	int index = -1;
	for (int i = (n >> 1); i >= 0; --i) {
		if (ans < s[i] + s[n] - s[n - (n >> 1) + i]) {
			ans = s[i] + s[n] - s[n - (n >> 1) + i];
			index = i;
		}
	}

	cout << ans << endl;
	for (int i = 0; i < index; ++i) printf("L");
	for (int i = n >> 1; i > index; --i) printf("R");
	printf("\n");

	return 0;
}