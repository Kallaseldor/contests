#include <bits/stdc++.h>
using namespace std;

int main() {

	string s;
	cin >> s;

	int freq[26];
	memset(freq, 0, sizeof freq);

	for (int i = 0; i < s.size(); ++i) freq[s[i] - 'a']++;

	int index = 0;
	for (int i = 0; i < s.size(); ++i) {
		
		while (!freq[index]) index++;
		freq[index]--;
		int id;

		if (s[i] != index + 'a') {
			for (int j = i; j < s.size(); ++j) {
				if (s[j] == index + 'a') {
					id = j;
					break;
				}
			}

			if (id != i) {
				printf("%d %d\n", id + 1, i + 1);
				swap(s[id], s[i]);
			}
		}
	}

	return 0;
}