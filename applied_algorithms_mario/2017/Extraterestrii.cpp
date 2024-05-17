#include<bits/stdc++.h>
using namespace std;

#define MOD 666013

struct pair_hash {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

int main()
{
	int n, m, k;
	// n = length of the word; m = number of letters; k = number of restrictions
	cin >> n >> m >> k;
	unordered_set<pair<int, int>, pair_hash> restrictions;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		restrictions.insert({a, b});
	}

	// dp[i][j] = number of words I can build of length i ending with j
	long long ans = 0;
	vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

	// base case
	for (int i = 1; i <= m; i++) {
		dp[1][i] = 1;
	}

	// Iterate over the length of the word
	for (int i = 2; i <= n; i++) {
		// Iterate over the last letter of the word
		for (int j = 1; j <= m; j++) {
			// Iterate over the second last letter of the word
			for (int k = 1; k <= m; k++) {
				if (restrictions.find({j, k}) != restrictions.end()) {
					continue;
				}
				// Add the number of words of length i-1 ending with k
				dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
			}
		}
	}

	// Sum the number of words of length n ending with any letter
	for (int i = 1; i <= m; i++) {
		ans = (ans + dp[n][i]) % MOD;
	}

	cout << ans;
	return 0;
}