#include <bits/stdc++.h>
using namespace std;
int n, m;

struct pair_hash {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int bfs(vector<vector<char>>& matrix,
		 unordered_set<pair<int, int>, pair_hash>& portals, pair<int, int> src,
		 pair<int, int> dst) {
	queue<pair<int, int>> q;
	int min_steps = -1;
	vector<vector<int>> distances(n, vector<int>(m, -1));
	distances[src.first][src.second] = 0;
	q.push(src);

	while (!q.empty()) {
		auto current = q.front(); q.pop();
		int x = current.first, y = current.second;
		if (current == dst) {
			return distances[x][y];
		}

		for (int i = 0; i < 4; i++) {
			int next_x = x + dx[i];
			int next_y = y + dy[i];
			if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) {
				continue;
			}

			if (matrix[next_x][next_y] == 'X') {
				continue;
			}

			if (distances[next_x][next_y] == -1) {
				distances[next_x][next_y] = 1 + distances[x][y];
				q.push({next_x, next_y});
			}

			if (matrix[next_x][next_y] == 'P') {
				for (auto portal : portals) {
					pair<int, int> next_portal = {next_x, next_y};
					if (portal != next_portal) {
						distances[portal.first][portal.second] = 1 + distances[x][y];
						q.push(portal);
					}
				}
			}
			
		}
	}

	return min_steps;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	vector<vector<char>> matrix(n, vector<char>(m));
	pair<int, int> src, dst;
	unordered_set<pair<int, int>, pair_hash> portals;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> matrix[i][j];
			if (matrix[i][j] == 'S') {
				src = {i, j};
			} else if (matrix[i][j] == 'D') {
				dst = {i, j};
			} else if (matrix[i][j] == 'P') {
				portals.insert({i, j});
			}
		}
	}

	int min_steps = bfs(matrix, portals, src, dst);
	cout << min_steps;
	return 0;
}