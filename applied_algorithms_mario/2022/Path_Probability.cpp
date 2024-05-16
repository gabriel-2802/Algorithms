#include <bits/stdc++.h>
using namespace std;

#define SCALE_FACTOR 1e4 * 1.0

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

const int NMAX = 150;

bool in_grid(int x, int y, int n, int m) {
	return (x >= 1 && x <= n) && (y >= 1 && y <= m);
}

void dfs(int x, int y, int n, int m, vector<vector<double>>& grid) {

}

int main() {
    ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	int start_row, start_col, end_row, end_col;
	cin >> start_row >> start_col >> end_row >> end_col;

	vector<vector<double>> grid(NMAX, vector<double>(NMAX, SCALE_FACTOR));

	unordered_set<pair<int, int>, pair_hash> vis;


	// for (int i = 1; i <= n; i++, cout << endl)
	// 	for (int j = 1; j <= m; j++)
	// 		cout << grid[i][j] << " ";

    return 0;
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};