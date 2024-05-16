#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n, skip;
	cin >> n;
	int ans = 0;
	vector<int> imp_meetings;
	for (int i = 0, imp, time; i < n ; i++) {
		cin >> imp >> time;
		if (imp == 0) {
			ans += time;
		} else {
			imp_meetings.push_back(time);
		}
	}

	cin >> skip;

	sort(imp_meetings.begin(), imp_meetings.end(), greater<int>());

	int i = 0;
	for (i = 0; i < imp_meetings.size() && skip; i++) {
		ans += imp_meetings[i];
		skip--;
	}

	if (skip) {
		cout << ans << "\n";
		return 0;
	}

	while (i < imp_meetings.size()) {
		ans -= imp_meetings[i++];
	}
	
	cout << ans;
    return 0;
}