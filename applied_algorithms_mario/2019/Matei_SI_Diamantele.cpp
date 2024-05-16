#include <bits/stdc++.h>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool in_grid(int x, int y, int n, int m) {
	return (x >= 1 && x <= n) && (y >= 1 && y <= m);
}

int main() {
	int N, M, P, L, C;
	cin >> N >> M >> P >> L >> C;
	vector<vector<int>> grid(N + 1, vector<int>(M + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> grid[i][j];
		}
	}
	vector<vector<int>> dist(N + 1, vector<int>(M + 1, -1));
	queue<pair<int, int>> q;
	q.push({L, C});
	dist[L][C] = 0;
	int max_beauty = grid[L][C];

	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int new_x = dx[i] + x;
			int new_y = dy[i] + y;
			
			if (in_grid(new_x, new_y, N, M) && dist[new_x][new_y] == -1) {
				dist[new_x][new_y] = 1 + dist[x][y];

				if (dist[new_x][new_y] > P) continue;

				q.push({new_x, new_y});
				max_beauty = max(max_beauty, grid[new_x][new_y]);
			}
		}
	}

	cout << max_beauty << "\n";
	return 0;
}