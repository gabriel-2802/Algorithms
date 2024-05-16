#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> cons(n);

	int max_cons = 0;
	int min_cons = 0;
	
	for (int i = 0; i < n; i++) {
		cin >> cons[i];
		if (cons[i] == 1) max_cons++;
	}

	for (int i = 0; i < n; i++) {
		if (cons[i] == 1) {
			min_cons++;
			i += 2;
		}
	}

	cout << min_cons << " " << max_cons;
	return 0;
}