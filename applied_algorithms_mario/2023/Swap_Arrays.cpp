#include <bits/stdc++.h>

using namespace std;

int n, k;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];

	long long sum = 0;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end(), greater<int>());

	for (int i = 0; i < n; i++) {
		if (k <= 0 || b[i] <= a[i]) break;
		
		swap(a[i], b[i]);
		k--;
	}

	sum = accumulate(a.begin(), a.end(), 0);
	cout << sum << "\n";

	return 0;
}
