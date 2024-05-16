#include <bits/stdc++.h>
using namespace std;

int mini = 1e9 + 1;
int end_node = -1;

void dfs(int node, unordered_set<int>& vis, vector<vector<pair<int, int>>>& adj) {
	vis.insert(node);
	end_node = node;

	for (auto [n, s] : adj[node]) {
		if (!vis.count(n)) {
			mini = min(mini, s);
			dfs(n, vis, adj);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int n, m, size;
	cin >> n >> m;
	unordered_set<int> goes_in;
	vector<vector<pair<int, int>>> adj(n + 1);

	for (int i = 0; i < m; i++) {
		int u, x;
		cin >> u >> x >> size;
		adj[u].push_back({x, size});
		goes_in.insert(x);
	}

	int cnt = n - goes_in.size();
	cout << cnt << "\n";

	unordered_set<int> vis;
	for (int i = 1; i <= n; i++) {
		if (!goes_in.count(i)) {
			dfs(i, vis, adj);
			if (mini == 1e9 + 1) mini = 0;
			cout << i << " " << end_node << " " << mini << "\n";
			mini = 1e9 + 1;
		}
	}
    return 0;
}
