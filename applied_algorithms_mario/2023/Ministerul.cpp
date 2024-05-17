#include <bits/stdc++.h>

using namespace std;

struct pair_hash {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

int n, m, q;

int manhattan(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

vector<vector<int>> roy_floyd(vector<vector<int>> cost) {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (cost[i][k] != 1e9 && cost[k][j] != 1e9)
					cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
			}
		}
	}

	return cost;
}

int main() {
	cin >> n >> m >> q;
	vector<pair<int, int>> coord(n + 1);
	vector<vector<int>> cost_manhattan(n + 1, vector<int>(n + 1, 1e9));
	vector<vector<int>> cost(n + 1, vector<int>(n + 1, 1e9));
	unordered_set<pair<int, int>, pair_hash> edges;

	for (int i = 1; i <= n; i++) cin >> coord[i].first >> coord[i].second;

	for (int i = 1; i <= m; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		cost[x][y] = cost[y][x] = c;
		edges.insert({x, y});
		edges.insert({y, x});
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!edges.count({i, j}) || !edges.count({j, i}))
				cost_manhattan[i][j] =
					manhattan(coord[i].first, coord[i].second, coord[j].first,
							  coord[j].second);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (cost[i][j] == 1e9) {
				cost[i][j] = cost_manhattan[i][j];
			}
		}
	}

	vector<vector<int>> min_cost = roy_floyd(cost);
	for (int i = 1; i <= q; i++) {
		int x, y;
		cin >> x >> y;
		cout << min_cost[x][y] << '\n';
	}

	return 0;
}
