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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v2-cafebabe-101/challenges/test-2-1-1-hard-disk-usoara/problem
class Solution {
    int n, k;
    vector<vector<int>> weights;

    long min_sum_for_k =  INF;

    int dx[3] = {0, 1, 1};
    int dy[3] = {1, 0, 1};
    public:
        void read() {
            cin >> n >> k;
            weights.resize(n, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> weights[i][j];
                }
            }
        }
        
        void solve() {
            vector<vector<vector<long>>> dp(n, vector<vector<long>>(n, vector<long>(k + 1, INF)));

            // dp[i][j][k] = min sum of weights to reach (i, j) with k cities from (0,0)
            dp[0][0][1] = weights[0][0];

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int s = 1; s <= k; ++s) {
                        // (i,j) - > (i + 1, j) or (i, j + 1) or (i + 1, j + 1)
                        if ( i == 0 && j == 0) {
                            continue;
                        }

                        if (i == 0) {
                            // first row
                            dp[i][j][s] = weights[i][j] + dp[i][j - 1][s - 1];
                        } else if (j == 0) {
                            // first column
                            dp[i][j][s] = weights[i][j] + dp[i - 1][j][s - 1];
                        } else {
                            dp[i][j][s] = weights[i][j] + min({dp[i - 1][j][s - 1], dp[i][j - 1][s - 1], dp[i - 1][j - 1][s - 1]});
                        }
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    min_sum_for_k = min(min_sum_for_k, dp[i][j][k]);
                }
            }
        }


        // works but highly inefficient
        void backtracking(pair<int,int> current, long sum, int city_n) {
            if (city_n ==  k) {
                min_sum_for_k = min(min_sum_for_k, sum);
                return;
            }

            int x = current.first;
            int y = current.second;

            pair<int, int> new_current;
            int min_weight = INF;

            for (int i = 0; i < 3; i++) {
                int new_x = x + dx[i];
                int new_y = y + dy[i];

                if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= n) {
                    continue;
                }

                int new_weight = weights[new_x][new_y];
                backtracking({new_x, new_y}, sum + new_weight, city_n + 1);
            }
        }

        void print() {
            cout << min_sum_for_k << endl;
        }
};

int main() {
    ios::sync_with_stdio(false);  
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}

// priority_queue<int, vector<int>, greater<int>> minHeap;
//  priority_queue<int> maxHeap;

// priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // compared by first element
//     priority_queue<pair<int, int>> maxHeap; // compared by first element




