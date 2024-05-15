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

class Solution {
    vector<vector<int>> graph;
    int n,m;
    vector<bool> is_factory;
    vector<bool> visited;
    public:
        void read() {
            cin >> n >> m;
            n++;
            graph.resize(n);
            is_factory.resize(n, false);
            visited.resize(n, false);
            for (int i = 0; i < m; i++) {
                int u,v;
                cin >> u >> v;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }

        void solve() {
            queue<int> q;
            q.push(1);
            visited[1] = true;
            // assume 1 is factory
            is_factory[1] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                        if (is_factory[u]) {
                            is_factory[v] = false;
                        } else {
                            is_factory[v] = true;
                        }
                    }
                }
            }
        }

        void print() {
            int factory_count = 0;
            for (int i = 1; i < n; i++) {
                if (is_factory[i]) {
                    factory_count++;
                }
            }

            cout << min(factory_count, n - 1 - factory_count) << endl;
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




