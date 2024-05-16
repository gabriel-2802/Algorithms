#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<double>> graph(n + 1, vector<double>(n + 1, -1));
	for (int i = 0; i < m; i++) {
		int u, v;
		double w;
		cin >> u >> v >> w;
		graph[u][v] = w;
	}

	for (int i = 1; i <= n; i++)
		graph[i][i] = 1;

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if ((graph[i][k] == -1) || (graph[k][j] == -1) || i == j) {
					continue;
				}

				if (graph[i][k] * graph[k][j] >= graph[i][j]) {
					graph[i][j] = graph[i][k] * graph[k][j];
				}
			}
		}
	}

	cout << fixed << setprecision(10);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
