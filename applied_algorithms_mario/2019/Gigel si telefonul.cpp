#include <bits/stdc++.h>
using namespace std;


int main() {
	int intersections, battery;
	int res = 0;
	int reset = 0;
	cin >> intersections >> battery;
	int curr_mini = 1e7;
	vector<int> cost(intersections);
	
	for (int i = 0; i < intersections; i++) {
		if (reset == battery) {
			reset = 0;
			curr_mini = 1e8;
		}
		reset++;
		cin >> cost[i];
		curr_mini = min(curr_mini, cost[i]);
		cost[i] = curr_mini; 
	}

// 2727553
// 5108327

	res = accumulate(cost.begin(), cost.end(), 0);
	cout << res << "\n";
    return 0;
}
