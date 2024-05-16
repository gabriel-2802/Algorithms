#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<bool> visited(1005, false);

bool check(vector<int>& candidate) {
	for (int i = 1; i < candidate.size(); i++) {
		if (candidate[i] % 2 == candidate[i - 1] % 2) return false;
	}

	return true;
}

void permutations(int n, vector<int>& curr) {
	if (curr.size() == n && check(curr)) {
		for (auto elem : curr) {
			cout << elem << " ";
		}

		cout << "\n";
	}

	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			visited[i] = true;
			curr.push_back(i);
			permutations(n, curr);
			curr.pop_back();
			visited[i] = false;
		}
	}
}


int main() {
    int n;
	cin >> n;
	if (n == 0) {
		cout << -1;
		return 0;
	}
	vector<int> curr;
	permutations(n, curr);
	return 0;
}