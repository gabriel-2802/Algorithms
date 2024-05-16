#include <bits/stdc++.h>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool in_mat(int x, int y, int n) {
	return (x >= 1 && x <= n) && (y >= 1 && y <= 2);
}

int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int road[n + 1][3];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 2; j++)
			cin >> road[i][j];
	
	int min_time = road[1][1];
	queue<int> q;

    return 0;
}