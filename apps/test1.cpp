#include <bits/stdc++.h>
using namespace std;

int n, start;

int main() {
	cin >> n;
	cin >> start;
	vector<vector<int>> jumps(n);

	for (int i = 0; i < n - 1; i++) {
		int k;
		cin >> k;
		for (int j = 0, x; j < k; j++) {
			cin >> x;
			jumps[i].push_back(x);
		}
	}

	vector<int> dp(n, INT_MAX);
	dp[start] = 0;

	for (int i = start; i < n; i++) {
		if (dp[i] != INT_MAX) {
			for (int jump : jumps[i]) {
				if (i + jump < n) dp[i + jump] = min(dp[i + jump], dp[i] + 1);
			}
		}
	}

	auto ans = dp[n - 1] == INT_MAX ? -1 : dp[n-1];
	cout << ans;

	return 0;
}
