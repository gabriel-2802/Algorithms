#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;


int main() {
	int N, M;
	cin >> N >> M;
	vector<int> adj[5005];
	int src;

	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// At position 0 are consumers, at position 1 are producers
	int cnt[2] = {0};
	src = 1;

	vector<bool> visited(N + 1, false);
	queue<pair<int, int>> q; // node and color
	
	q.push({src, 0});
	visited[src] = true;

	while (!q.empty()) {
		auto [node, color] = q.front(); q.pop();
		cnt[color]++;
		
		for (auto neigh : adj[node]) {
			if (!visited[neigh]) {
				visited[neigh] = true;
				q.push({neigh, 1 - color});
			}
		}
	}


	cout << min(cnt[0], cnt[1]) << endl;
	return 0;
}
