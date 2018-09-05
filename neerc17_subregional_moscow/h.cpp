#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112345;

long long temp[MAXN];
long long tim[MAXN];

int main () {

	// ios :: sync_with_stdio (false); cin.tie (NULL); cout.tie (NULL);

	long long T, t, n;		// T - Temperatura Total
							// t - Tempo
							// n - Regras
	cin >> T >> t >> n;

	for (int i = 0; i < n; ++i)
		scanf ("%lld %lld", tim + i, temp + i);


	long long maxtemp = 0LL;
	long long mintemp = 0LL;
	for (int i = 1; i < n; ++i) {
		long long val = 0;
		long long diff = temp[i] - temp[i - 1];
		if (diff < 0) diff *= -1LL;

		if (tim[i] - tim[i - 1] < diff) {
			cout << "No" << endl;
			return 0;
		}

		long long deltatim = tim[i] - tim[i - 1];
		long long fr = tim[i] - tim[i - 1] - diff;

		if (temp[i] >= temp[i - 1]) {
			// Max
			// Primeiro eu subo ate B, dai subo meio fr e desco meio fr

			val = a * deltat;
			val += ((1LL + diff) * diff) >> 1LL;
			
			// Triangulo pra cima e pra baixo
			long long up = fr >> 1LL;
			val += ((1LL + up) * up);
			val += (fr & 1) ? up : 0;
			val -= temp[i];

			maxtemp += val;


			// @@@@@@@@@@@@@@@@@@
			// Min

		} else {
			// Max
			// Primeiro eu subo meio fr, dps desco ate B
			
			val = a * deltat;
			// Triangulo pra cima e pra baixo
			long long up = fr >> 1LL;
			val += ((1LL + up) * up);
			val += (fr & 1) ? up : 0;

			// Descida
			val -= ((1LL + diff) * diff) >> 1LL;
			val -= temp[i];

			maxtemp += val;
		}
	}

	maxtemp += temp[0] * (tim[0] - 1);
	maxtemp += (tim[0] * (tim[0] - 1)) >> 1LL;

	maxtemp += temp[n - 1] * ()

	return 0;
}