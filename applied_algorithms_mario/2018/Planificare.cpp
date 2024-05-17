#include <bits/stdc++.h>
using namespace std;

int n, m, p;

vector<int> topo_sort(vector<vector<int>>& courses) {
	vector<int> indeg(n + 5, 0);
	for (int i = 1; i <= n; i++) {
		for (auto course : courses[i]) {
			indeg[course]++;
		}
	}

	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (indeg[i] == 0) {
			q.push(i);
		}
	}

	vector<int> order;
	while (!q.empty()) {
		int course = q.front(); q.pop();
		order.push_back(course);

		for (auto next_course : courses[course]) {
			indeg[next_course]--;
			if (indeg[next_course] == 0) {
				q.push(next_course);
			}
		}
	}

	return order;
}

bool check(vector<int>& order, vector<int>& to_check_good_order) {
	unordered_map<int, int> position;
	for (int i = 0; i < n; i++) {
		position[order[i]] = i;
	}

	for (int i = 0; i < n; i++) {
		if (position[to_check_good_order[i]] > i) {
			return false;
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> p;
	vector<vector<int>> courses(n + 5);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		courses[u].push_back(v);
	}
	
	vector<int> order = topo_sort(courses);
	
	vector<int> to_check_good_order(n);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < n; j++) {
			cin >> to_check_good_order[j];
		}

		if (check(order, to_check_good_order)) {
			cout << "DA\n";
		} else {
			cout << "NU\n";
		}
	}

    return 0;
}