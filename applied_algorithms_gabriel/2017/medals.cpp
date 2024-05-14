#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <unordered_set>
#include <functional>
#include <algorithm>

using namespace std;
#define INF numeric_limits<int>::max()

// add this to use pair as key in unordered_map and unordered_set
struct pair_hash {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};


// https://www.hackerrank.com/contests/test-practic-pa-2017-v2-meeseeks/challenges/test-2-olimpiada-usoara/problem
// 50% score
class Solution {
	int n, p;
	vector<double> probabilities;

	vector<double> win_probabilities;
	vector<bool> visited;
	public:
		void read() {
			cin >> n >> p;
			n++;
			probabilities = vector<double>(n);

			for (int i = 1; i < n; i++) {
				cin >> probabilities[i];
			}
		}
		
		void arrangements(vector<int> current) {
			if (current.size() == p) {
				compute_prob(current);
				return;
			}

			for (int i = 1; i < n; i++) {
				if (visited[i]) {
					continue;
				}

				visited[i] = true;
				current.push_back(i);
				arrangements(current);
				current.pop_back();
				visited[i] = false;
			}
		}

		void compute_prob(vector<int> current) {
			double prob = 1;
			for (int i = 0; i < p; i++) {
				prob *= probabilities[current[i]];
			}

			win_probabilities.push_back(prob);

		}
		

		void solve() {
			vector<int> current;
			visited = vector<bool>(n, false);
			arrangements(current);
		   
		}

		void print() {
			double sum = 0;
			for (double prob : win_probabilities) {
				sum += prob;
			}

			sum /= win_probabilities.size();
			printf("%.6f\n", sum);
		}
};

int main() {
	std::ios::sync_with_stdio(false);  
	Solution solution;
	solution.read();
	solution.solve();
	solution.print();
	return 0;
}