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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v1-deadbeef/challenges/test-1-2-2-max-packet-size-medie
class Solution {
    int n,m;
    vector<vector<pair<int,int>>> graph;

    vector<int> in_degree;
    vector<bool> visited;

    vector<tuple<int,int,int>> paths; // start - end - min_weight
    public:
        void read() {
            cin >> n >> m;
            n++;
            graph.resize(n);
            visited.resize(n, false);
            in_degree.resize(n, 0);
            for(int i=0;i<m;i++){
                int u,v,w;
                cin >> u >> v >> w;
                graph[u].push_back({v,w});
                in_degree[v]++;
            }
        }

        void solve() {

            for (int i = 1; i < n; i++) {
                if (in_degree[i] == 0) {
                    tuple<int,int,int> path = {i, i, INF};
                    dfs(path, i);
                    paths.push_back(path);
                }
            }
        }

        void dfs(tuple<int,int,int>& path, int u) {
            visited[u] = true;

            for (auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                path = {get<0>(path), v, min(get<2>(path), w)};
                if (!visited[v]) {
                    dfs(path, v);
                }
            }

           
        }

        

        void print() {
            cout << paths.size() << endl;
            for (auto& path : paths) {
                cout << get<0>(path) << " " << get<1>(path) << " " << (get<2>(path) == INF ? 0 : get<2>(path)) << endl;
            }
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




