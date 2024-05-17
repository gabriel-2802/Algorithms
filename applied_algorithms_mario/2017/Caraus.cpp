#include <bits/stdc++.h>
using namespace std;

bool can_carry(int power, vector<int>& v, int limit) {
	int curr_weight = 0;
	for (int i = 0; i < v.size(); i++) {
		if (curr_weight > power) {
			curr_weight = v[i];
			limit--;
			if (limit <= 0) return false;
		} else {
			curr_weight += v[i];
		}
	}

	return true;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n, limit;
	cin >> n >> limit;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	int left = *max_element(v.begin(), v.end());
	int right = accumulate(v.begin(), v.end(), 0);

	while (left < right) {
		int mid = (left + right) / 2;
		if (can_carry(mid, v, limit)) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	cout << left;
	return 0;
}
