#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10005];
bool visited[10005];
int dp[10005];

// Returns the longest path starting from node
int dfs(int node) {
	visited[node] = 1;
	int max_path = 0;

	for (auto it : adj[node])
		if(!visited[it])
			max_path = max(max_path, dfs(it));

	visited[node] = 0;
	dp[node] = 1 + max_path;
	return dp[node];
}

int main() {
	int N;
	cin >> N;
	for(int i = 1; i <= N; i++) {
		int L;
		cin >> L;
		adj[i].push_back(L);
	}

	int max_pages = 0;
	// Find longest path from each node
	for (int i = 1; i <= N; i++)
		max_pages = max(max_pages, dfs(i));

	cout << max_pages << endl;
	return 0;
}
