#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <unordered_set>
#include <functional>
#include <algorithm>
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


// https://www.hackerrank.com/contests/test-practic-pa-2-illidan/challenges/topsort-problema-usoara/problem
class Solution {
    vector<vector<int>> graph;
    vector<int> in_degree;
    int n;

    unordered_map<int, int> node_value;

    public:
        void read() {
            int m;
            cin >> n >> m;

            n += 1; // 1-indexed

            graph.resize(n);
            in_degree.resize(n, 0);

            for (int i = 1; i < n; i++) {
                int value;
                cin >> value;
                node_value[i] = value;
            }

            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                graph[u].push_back(v);
                in_degree[v]++;
            }
        }

        void solve() {
            // find minimum lexicographically topological sort
            cout << top_sort() << endl;
        }

        // returns it as a string of values
        string top_sort() {
            vector<bool> visited(n, false);

            vector<int> sorted;
            vector<int> in_degree_copy = vector<int>(in_degree);

            priority_queue<pair<int, int>, vector<pair<int, int>>> q;
            

            for (int i = 1; i < n; i++) {
                if (in_degree_copy[i] == 0) {
                    q.push({node_value[i], i});
                }
            }

            while (!q.empty()) {
               auto value_node = q.top();
                int u = value_node.second;
                q.pop();
                sorted.push_back(u);

                for (int v : graph[u]) {
                    in_degree_copy[v]--;
                    if (in_degree_copy[v] == 0) {
                        q.push({node_value[v], v});
                    }
                }
            }

            string result = "";
            for (int i = 0; i < n - 1; i++) {
                result += to_string((node_value[sorted[i]])) + " ";
            }

            return result;
        }

        void print() {
            // code here
        }
};

int main() {
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}