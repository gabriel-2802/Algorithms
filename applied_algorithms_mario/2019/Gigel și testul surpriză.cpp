#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> problems(n + 1);
	for (int i = 0; i < n; i++)
		cin >> problems[i];
	
	sort(problems.begin(), problems.end());
	int start = 0;
	int end = start + k - 1;
	int best_diff = INT_MAX, best_start = -1;

	while (end < problems.size()) {
		if (problems[end] - problems[start] < best_diff) {
			best_diff = problems[end] - problems[start];
			best_start = start;
		}

		start++;
		end++;
	}

	cout << best_diff << "\n";
	for (int i = best_start; i < best_start + k; i++) {
		cout << problems[i] << " ";
	}
	
    return 0;
}
