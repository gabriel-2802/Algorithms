#include <bits/stdc++.h>
using namespace std;

void dfs(unordered_set<int>& v, int node, vector<vector<int>>& adj) {
	v.insert(node);
	for (auto n : adj[node])
		if (!v.count(n))
			dfs(v, n, adj);
}


int main() {
    std::ios::sync_with_stdio(false);  
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n + 1);

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	unordered_set<int> visited;
	int to_connect = 0;
	for (int i = 1; i <= n; i++) {
		if (!visited.count(i)) {
			dfs(visited, i, adj);
			to_connect++;
		}
	}

	cout << to_connect - 1;
    return 0;
}