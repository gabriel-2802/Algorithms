#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <string>

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
// https://www.hackerrank.com/contests/colocviu-324cab-98becc/challenges/ministerul-medie/submissions/code/1378115148
class Solution {
    int n,m;
    vector<vector<int>> cities; // 1 indexed matrix
    vector<pair<int, int>> city_idx_pairs;

    unordered_map<int, pair<int, int>> city_to_coords;
    unordered_map<pair<int, int>, int, pair_hash> coords_to_city;

    public:
        void read() {
            int q;
            cin >> n >> m >> q; // 1 indexed

            for (int i = 1;i <= n; ++i) {
                int x,y;
                cin >> x >> y;
                city_to_coords[i] = {x,y};
                coords_to_city[{x,y}] = i;
            }

            n++;
            cities = vector<vector<int>>(n, vector<int>(n, INF));
            for (int i = 1; i < n; ++i) {
                cities[i][i] = 0;
            }

            for (int i = 0; i < m; ++i) {
                int a,b,c;
                cin >> a >> b >> c;
                cities[a][b] = c;
                cities[b][a] = c;
            }

            for (int i = 0; i < q; ++i) {
                int a,b;
                cin >> a >> b;
                city_idx_pairs.push_back({a,b});
            }
        }

        int manhattan_dis(pair<int, int> a, pair<int, int> b) {
            return abs(a.first - b.first) + abs(a.second - b.second);
        }

        vector<vector<int>> floyd_warshall() {
            vector<vector<int>> dist = cities;

            for (int k = 1; k < n; ++k) {
                for (int i = 1; i < n; ++i) {
                    for (int j = 1; j < n; ++j) {
                        if (dist[i][k] != INF && dist[k][j] != INF) {
                            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }

            return dist;
        }

        void solve() {
            vector<vector<int>> inital_dist = floyd_warshall();

            // try to build rodes where no rode exists
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (cities[i][j] == INF) {
                        cities[i][j] = manhattan_dis(city_to_coords[i], city_to_coords[j]);
                    }
                }
            }

            vector<vector<int>> final_dist = floyd_warshall();
            for (auto [a,b] : city_idx_pairs) {
                int initial = inital_dist[a][b];
                int final = final_dist[a][b];

                if (initial > final) {
                    cout << final << endl;
                } else {
                    cout << initial << endl;
                }
            }


        }

        void print() {
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




