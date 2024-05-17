#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;

void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& cities) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					cities[i][j] = cities[i][k] + cities[k][j];
				} else if (dist[i][j] == dist[i][k] + dist[k][j]) {
					cities[i][j] =
						max(cities[i][j], cities[i][k] + cities[k][j]);
				}
			}
		}
	}
}

void printMatrix(const vector<vector<int>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			cout << elem << " ";
		}
		cout << "\n";
	}
}

int main() {
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (auto& row : matrix)
		for (auto& elem : row) cin >> elem;

	vector<vector<int>> cities(n, vector<int>(n, 1));
	for (int i = 0; i < n; i++) {
		cities[i][i] = 0;
	}

	floydWarshall(matrix, cities);

	printMatrix(matrix);
	printMatrix(cities);

	return 0;
}
