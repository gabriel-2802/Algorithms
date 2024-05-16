#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int l_stars = 0, r_stars = 0, pairs = 0;
	vector<int> left(300, 0);
	vector<int> right(300, 0);

	for (int i = 0; i < n; i++) {
		char letter;
		cin >> letter;
		if (letter == '*') {
			l_stars++;
			continue;
		}

		left[letter]++;
	}
	
	for (int i = 0; i < n; i++) {
		char letter;
		cin >> letter;
		if (letter == '*') {
			r_stars++;
			continue;
		}

		right[letter]++;
	}

	for (char ch = 'a'; ch <= 'z'; ch++) {
		int nr_left = left[ch];
		int nr_right = right[ch];

		if (nr_left > nr_right) {
			pairs += nr_right;
			nr_left -= nr_right;
			pairs += min(nr_left, r_stars);
			r_stars -= min(nr_left, r_stars);
			if (r_stars <= 0) r_stars = 0; 
		} else if (nr_right > nr_left) {
			pairs += nr_left;
			nr_right -= nr_left;
			pairs += min(nr_right, l_stars);
			l_stars -= min(nr_right, l_stars);
			if (l_stars <= 0) l_stars = 0;
		} else {
			pairs += nr_left;
		}
	}

	pairs += min(l_stars, r_stars);
	cout << pairs << "\n";
    return 0;
}
