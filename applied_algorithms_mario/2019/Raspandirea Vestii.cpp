#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, m;
	cin >> n >> m;
	vector<vector<int>> friends(n + 5);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		friends[u].push_back(v);
		friends[v].push_back(u);
	}

	queue<int> q;
	vector<int> dist(n + 5, -1);
	int src = 1;
	q.push(src);
	dist[src] = 0;

	while (!q.empty()) {
		int node = q.front(); q.pop();

		for (auto neigh : friends[node]) {
			if (dist[neigh] == -1) {
				dist[neigh] = dist[node] + 1;
				q.push(neigh);
			}
		}
	}

	cout << *max_element(dist.begin(), dist.end());
    return 0;
}
