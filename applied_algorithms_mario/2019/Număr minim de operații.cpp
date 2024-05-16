#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int src, dest;
    int operations = 0;

	cin >> n;
	vector<int> values(n);
	for (int i = 0; i < n; i++) {
		cin >> values[i];
	}

	cin >> src >> dest;
	queue<pair<int,int>> q;
	unordered_set<int> visited;
	q.push({src, 0});
	visited.insert(src);

	while (!q.empty()) {
		auto [node, op] = q.front(); q.pop();
		if (node == dest) {
			cout << op << "\n";
			return 0;
		}

		for (int num : values) {
			int next_plus = node + num;
			int next_minus = node - num;

			if (!visited.count(next_plus)) {
				visited.insert(next_plus);
				q.push({next_plus, op + 1});
			}

			if (!visited.count(next_minus)) {
				visited.insert(next_minus);
				q.push({next_minus, op + 1});
			}
		}
	}

	cout << operations << "\n";

    return 0;
}