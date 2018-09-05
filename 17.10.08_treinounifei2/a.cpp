#include <bits/stdc++.h>
using namespace std;

string s;



int main() {

	cin >> s;

	long long a[3];
	long long ans = 0;
	
	memset(a, 0, sizeof a);
	a[0]++;

	long long sum = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= '0' && s[i] <= '9') {
			sum += (s[i] - '0');
			sum %= 3;
			a[sum]++;
		}  else {
			sum = 0;
			//printf("a0, a1, a2 = %lld %lld %lld\n", a[0], a[1], a[2]);
			ans += a[0] * (a[0] - 1LL);
			ans += a[1] * (a[1] - 1LL);
			ans += a[2] * (a[2] - 1LL);
			//cout << "ans = " << ans << endl;
			memset(a, 0, sizeof a);
			a[0]++;
		}
	}

	ans += a[0] * (a[0] - 1LL);
	ans += a[1] * (a[1] - 1LL);
	ans += a[2] * (a[2] - 1LL);
			

	cout << (ans >> 1) << endl;

	return 0;
}