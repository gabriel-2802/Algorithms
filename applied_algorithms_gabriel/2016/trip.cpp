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

// https://www.hackerrank.com/contests/test-practic-pa-2-malfurion/challenges/magazine-problema-usoara/problem
class Solution {
    vector<vector<int>> graph_w;
    int n;

    vector<vector<int>> parents;
    vector<vector<int>> distances;
    vector<vector<int>> nodes_per_path;

    public:
        void read() {
            cin >> n;
            n += 1;
            graph_w = vector<vector<int>>(n, vector<int>(n, 0));

            for (int i = 1; i < n; i++) {
                for (int j = 1; j < n; j++) {
                    cin >> graph_w[i][j];
                }
            }
        }

        void solve() {
            floyd_warshall();
            // print distances
        }

        void floyd_warshall() {
            distances = vector<vector<int>>(n, vector<int>(n, INF));
            parents = vector<vector<int>>(n, vector<int>(n, -1));
            nodes_per_path = vector<vector<int>>(n, vector<int>(n, 0));

            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (i == j) {
                        distances[i][j] = 0;
                    } else {
                        distances[i][j] = graph_w[i][j];
                        parents[i][j] = i;
                        nodes_per_path[i][j] = 2;
                    }
                }
            }

            for (int k = 1; k < n; ++k) {
                for (int i = 1; i < n; ++i) {
                    for (int j = 1; j < n; ++j) {
                        if (distances[i][k] + distances[k][j] < distances[i][j]) {
                            distances[i][j] = distances[i][k] + distances[k][j];
                            parents[i][j] = parents[k][j];
                            nodes_per_path[i][j] = nodes_per_path[i][k] + nodes_per_path[k][j] - 1;
                        } else if (distances[i][k] + distances[k][j] == distances[i][j]) {
                            if (nodes_per_path[i][k] + nodes_per_path[k][j] - 1 > nodes_per_path[i][j]) {
                                parents[i][j] = parents[k][j];
                                nodes_per_path[i][j] = nodes_per_path[i][k] + nodes_per_path[k][j] - 1;
                            }
                        }
                    }
                }
            }
        }

        void print() {
            for (int i = 1; i < n; i++) {
                for (int j = 1; j < n; j++) {
                    cout << distances[i][j] << " ";
                }
                cout << endl;
            }

            for (int i = 1; i < n; i++) {
                for (int j = 1; j < n; j++) {
                    if (nodes_per_path[i][j] == 0) {
                        cout << 0 << " ";
                    } else {
                        cout << nodes_per_path[i][j] + 1 << " ";
                    }
                }
                cout << endl;
            }
        }
};

int main() {
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}