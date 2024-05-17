#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

struct pair_hash {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

struct compare {
	bool operator()(const pair<int, pair<int, int>>& a,
					const pair<int, pair<int, int>>& b) const {
		return a.first > b.first;
	}
};

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n;
int road[3][1000001];

bool in_mat(int x, int y) { return x >= 1 && x <= 2 && y >= 1 && y <= n; }

int dijkstra(unordered_map<pair<int, int>, int, pair_hash>& dist) {
	unordered_set<pair<int, int>, pair_hash> vis;
	pair<int, int> src = {1, 1};

	dist[src] = road[1][1];

	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
				   compare>
		pq;

	pq.push({dist[src], src});
	while (!pq.empty()) {
		auto [d, node] = pq.top(); pq.pop();

		if (vis.count(node)) continue;
		vis.insert(node);

		for (int i = 0; i < 4; i++) {
			int new_x = dx[i] + node.first;
			int new_y = dy[i] + node.second;

			if (in_mat(new_x, new_y) && road[new_x][new_y] != -1 &&
				!vis.count({new_x, new_y}) &&
				d + road[new_x][new_y] < dist[{new_x, new_y}]) {
				dist[{new_x, new_y}] = d + road[new_x][new_y];
				pq.push({dist[{new_x, new_y}], {new_x, new_y}});
			}
		}
	}

	pair<int, int> dst = {2, n};
	return dist[dst];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	unordered_map<pair<int, int>, int, pair_hash> dist;

	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> road[i][j];
			dist[{i, j}] = INF;
		}
	}

	cout << dijkstra(dist);
	return 0;
}
