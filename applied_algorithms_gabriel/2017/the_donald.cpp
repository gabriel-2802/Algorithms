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

// https://www.hackerrank.com/contests/test-practic-pa-2017-v2-meeseeks/challenges/test-2-thedonald-usoara/problem
class Solution {
    int n,m;
    vector<vector<int>> graph;

    int connected_comp = 0;
    vector<bool> visited;
    public:
        void read() {
            cin >> n >> m;
            n++;
            graph.resize(n);
            for (int i = 0; i < m; i++) {
                int a, b;
                cin >> a >> b;
                graph[a].push_back(b);
                graph[b].push_back(a);
            }

        }

        void solve() {
            visited = vector<bool>(n, false);

            for (int node = 1; node < n; ++node) {
                if (!visited[node]) {
                    dfs(node);
                    connected_comp++;
                }
            }
        }

        void dfs(int src) {
            visited[src] = true;
            for (int neighbor : graph[src]) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        
        }

        void print() {
            cout << connected_comp - 1 << endl;
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