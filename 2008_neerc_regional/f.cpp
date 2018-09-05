#include <bits/stdc++.h>
using namespace std;


long long memo3[312][2];
long long achakth(int pos, bool open) {
	if (pos == 0) return 0;
	if (pos == 1)
		if (open) return 2;
		else return 1;
		
	long long &p = memo3[pos][open];
	if (p != -1LL) return p;
	
	p = 0;
	if (open) p = achakth(pos - 1, 0);
	p += achakth(pos - 1, 1);
	
	return p; 
}

string nth;

void submain(long long n, long long k) {

	memset(memo3, -1, sizeof memo3);
	
	k--;
	
	string ans;
	
	bool open = true;
	for (int i = n; i > 1; --i) {
		if (achakth(i - 1, 1) <= k) {
			k -= achakth(i - 1, 1);
			ans += "1";
			open = false;
		} else {
			ans += "0";
			open = true;
		}
	}
	
	if (k == 0) ans += "0";
	else ans += "1";	
	
	nth = ans;
	return;
}

long long memo1[312][2];	// Qtd de digitos
long long memo2[312][2];



long long contaNums (int pos, bool open) {
	if (pos == 0) return 1 + open;
	
	long long &p = memo2[pos][open];
	if (p != -1LL) return p;
	
	p = contaNums(pos - 1, 1);
	if (open) {
		p += contaNums(pos - 1, 0);
	}
	
	return p;
}

long long conta1(int pos, bool open) {
	if (pos == 0) return open;
	
	long long &p = memo1[pos][open];
	if (p != -1LL) return p;
	
	p = conta1(pos - 1, 1);	// Coloquei um 0
	if (open) {
		p += conta1(pos - 1, 0) + contaNums(pos - 1, 0);	// Colquei um 1
	}
	
	return p;
}



long long fib[312];

int main() {

	long long n;
	cin >> n;

	if (n <= 10) {
		fib[0] = 0;
		fib[1] = 1;
		fib[2] = 2;
		fib[3] = 2;
		fib[4] = 3;
		fib[5] = 3;
		fib[6] = 3;
		fib[7] = 4;
		fib[8] = 4;
		fib[9] = 5;
		fib[10] = 6;
		
		cout << fib[n] << endl;
		return 0;
	}
	
	
	memset(memo1, -1LL, sizeof memo1);
	memset(memo2, -1LL, sizeof memo2);
	
	fib[1] = 1;
	fib[2] = 1;
	fib[0] = 0;
	
	long long ans = 0;
	long long q = 1;
	int siz = 1;
	
	for (long long i = 1; i < 301; ++i) {
		q += (i + 1LL) * contaNums(i - 1, 0);
		// cout << i + 1 << " " << contaNums(i - 1, 0) << " " << q << endl;
		if (q == n) {
			cout << conta1(i, 1) << endl;
			return 0;
		}
		cout << q << " " << n << endl;
		if (q > n) {
			ans += conta1(i - 1, 1);
			break;
		}
		siz += contaNums(i - 1, 0);
	}

	cout << ans << endl;
	
	submain(5, siz);
	cout << nth << endl;
		
			
	return 0;
}
