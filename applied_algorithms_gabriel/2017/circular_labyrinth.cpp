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


// https://www.hackerrank.com/contests/test-practic-pa-2017-v1-plumbus/challenges/test-1-2-2-medii/problem
class Solution {
    vector<vector<char>> maze;
    int n, m;
    unordered_set<pair<int,int>, pair_hash> visited;

    unordered_set<pair<int,int>, pair_hash> gates;
    vector<vector<int>> distances;

    public:
        void read() {
           cin >> n >> m;

            maze = vector<vector<char>>(n, vector<char>(m));
            distances = vector<vector<int>>(n, vector<int>(m, INF));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cin >> maze[i][j];
                    if (maze[i][j] == 'G') {
                        gates.insert({i,j});
                        distances[i][j] = 0;
                    }
                }
            }
        }

        // closest distance from gates to all other cells
        void solve() {
            int dl[] = {-1, 0, 1, 0};
            int dc[] = {0, 1, 0, -1};

            queue<pair<int,int>> q;
            for (auto gate : gates) {
                q.push(gate);
            }

            while (!q.empty()) {
                auto point = q.front();
                int x = point.first;
                int y = point.second;

                q.pop();

                for (int i = 0; i < 4; ++i) {
                    int new_x = x + dl[i];
                    int new_y = y + dc[i];

                    auto circular_point = circular_position(new_x, new_y);
                    new_x = circular_point.first;
                    new_y = circular_point.second;

                    if (maze[new_x][new_y] == 'X') {
                        continue;
                    }

                    if (distances[new_x][new_y] > distances[x][y] + 1) {
                        distances[new_x][new_y] = distances[x][y] + 1;
                        q.push({new_x, new_y});
                    }
                }
            }

        }

        pair<int, int> circular_position(int x, int y) {
            if (x == -1) {
                x = n - 1;
            }

            if (x == n) {
                x = 0;
            }

            if (y == -1) {
                y = m - 1;
            }

            if (y == m) {
                y = 0;
            }

            return {x, y};

        }

        void print() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (distances[i][j] == INF) {
                        cout << "-1 ";
                    } else {
                        cout << distances[i][j] << " ";
                    }
                }
                cout << endl;
            }
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