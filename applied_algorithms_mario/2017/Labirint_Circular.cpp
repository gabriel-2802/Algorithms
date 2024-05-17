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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int n, m;

pair<int, int> next_pos(int x, int y) {
	if (x == n) x = 0;
	if (x == -1) x = n - 1;
	if (y == m) y = 0;
	if (y == -1) y = m - 1;
	return {x, y};
}

void bfs(vector<vector<char>>& matrix,
		 unordered_set<pair<int, int>, pair_hash>& exits,
		 vector<vector<int>>& distances) {
	queue<pair<int, int>> q;
	for (auto exit : exits) {
		q.push(exit);
	}

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_x = current.first + dx[i];
			int next_y = current.second + dy[i];
			tie(next_x, next_y) = next_pos(next_x, next_y);

			if (distances[next_x][next_y] == INT_MAX) {
				if (matrix[next_x][next_y] == 'X') {
					continue;
				} else {
					distances[next_x][next_y] =
						min(1 + distances[current.first][current.second],
							distances[next_x][next_y]);
					q.push({next_x, next_y});
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	vector<vector<char>> matrix(n, vector<char>(m));
	unordered_set<pair<int, int>, pair_hash> exits;
	vector<vector<int>> distances(n, vector<int>(m, INT_MAX));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> matrix[i][j];
			if (matrix[i][j] == 'G') {
				exits.insert({i, j});
				distances[i][j] = 0;
			}
		}
	}

	bfs(matrix, exits, distances);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (distances[i][j] == INT_MAX) distances[i][j] = -1;
			cout << distances[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
