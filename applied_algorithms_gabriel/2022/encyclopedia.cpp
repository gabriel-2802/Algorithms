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

class Solution {
    int n;
    vector<int> fathers;
    unordered_map<int, int> graph;
    vector<bool> visited;
    int longest_path = -INF;

public:
    void read() {
        cin >> n;
        n++;
        fathers.resize(n);
        visited.resize(n, false);
        for (int i = 1; i < n; i++) {
            cin >> fathers[i];
        }
    }

    void solve() {
        rebuild_graph();
        for (int i = 1; i < n; i++) {
            dfs(i, 0);
        }
    }

    void dfs(int node, int depth) {
        if (visited[node])
            return;
        visited[node] = true;
        depth++;
        longest_path = max(longest_path, depth);
    
        if (graph.find(node) != graph.end()) {
            dfs(graph[node], depth);
        }
        visited[node] = false;
    }

    void rebuild_graph() {
        for (int i = 1; i < n; i++) {
            graph[i] = fathers[i];
        }
    }

    void print() {
        cout << longest_path << endl;
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