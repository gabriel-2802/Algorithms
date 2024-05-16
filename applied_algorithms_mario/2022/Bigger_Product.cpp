#include <bits/stdc++.h>

using namespace std;
#define INF numeric_limits<int>::max()

typedef long long ll;
typedef unsigned long long ull;

class Solution {
 public:
	int n;
	vector<int> elems;
	int cardinal = 0;

   	void read() {
		cin >> n;
		elems.resize(n);
		for (int i = 0; i < n; i++)
			cin >> elems[i];
	}

	void solve() {
		vector<double> logs(n);
		double total_sum = 0;
		for (int i = 0; i < n; i++) {
			logs[i] = log(elems[i]);
			total_sum += logs[i];
		}

		sort(logs.begin(), logs.end(), greater<double>());
		double sum_start = 0;
		double sum_end = total_sum;

		for (int i = 0; i < n; i++) {
			if (sum_start >= sum_end) {
				cardinal = i;
				break;
			}

			sum_start += logs[i];
			sum_end -= logs[i];
		}

		if (cardinal == 0)
			cardinal = n;
	}

	void print() {
		cout << cardinal << endl;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	Solution *s = new Solution();
	s->read();
	s->solve();
	s->print();
	delete s;
	return 0;
}
