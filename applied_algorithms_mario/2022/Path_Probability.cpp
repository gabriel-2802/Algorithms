#include <bits/stdc++.h>
using namespace std;

#define SCALE_FACTOR 1e4 * 1.0

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

const int NMAX = 150;

bool in_grid(int x, int y, int n, int m) {
	return (x >= 0 && x < n) && (y >= 0 && y < m);
}

double neighbor_prob(int x, int y, int n, int m, vector<vector<double>>& grid) {
	double prob = 0;
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (in_grid(nx, ny, n, m)) {
			cnt++;
			prob += grid[nx][ny];
		}
	}

	if (cnt == 0) return 0;
	return prob / cnt;
}

void dfs(int x, int y, int n, int m, vector<vector<double>>& grid, unordered_set<pair<int, int>, pair_hash>& vis) {
	if (vis.find({x, y}) != vis.end()) return;
	vis.insert({x, y});
	
	double prob = neighbor_prob(x, y, n, m, grid);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (in_grid(nx, ny, n, m) && vis.find({nx, ny}) == vis.end()) {
			grid[nx][ny] = prob;
			dfs(nx, ny, n, m, grid, vis);
		}
	}
}


int main() {
    ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	int start_row, start_col, end_row, end_col;
	cin >> start_row >> start_col >> end_row >> end_col;

	vector<vector<double>> grid(NMAX, vector<double>(NMAX, 0));
	unordered_set<pair<int, int>, pair_hash> vis;

	grid[start_row][start_col] = 1.0 * SCALE_FACTOR;
	cout << neighbor_prob(0, 1, n, m, grid) << endl << endl;

	dfs(start_row, start_col, n, m, grid, vis);

	// for (int i = 0; i < n; i++, cout << endl)
	// 	for (int j = 0; j < m; j++)
	// 		cout << grid[i][j] << " ";

	// cout << fixed << setprecision(3) << grid[end_row][end_col] << endl;
    return 0;
}
