#include <bits/stdc++.h>
using namespace std;

char find_best_ch(char neigh_left, char neigh_right) {
	char best_ch = 'a';
	while (true) {
		if (neigh_left == best_ch || best_ch == neigh_right) {
			best_ch++;
			continue;
		} else {
			return best_ch;
		}
	}
}

char find_best_ch(char neigh_left) {
	char best_ch = 'a';
	while (true) {
		if (neigh_left == best_ch) {
			best_ch++;
			continue;
		} else {
			return best_ch;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	string sir;
	cin >> sir;

	for (int i = 0; i < sir.size(); i++) {
		if (sir[i] == '_') {
			if (i == sir.size() - 1) {
				sir[i] = find_best_ch(sir[i - 1]);
			} else {
				sir[i] = find_best_ch(sir[i - 1], sir[i + 1]);
			}
		}
	}

	cout << sir + '\n';
    return 0;
}