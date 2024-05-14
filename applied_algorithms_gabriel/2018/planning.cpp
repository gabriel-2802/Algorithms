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


// https://www.hackerrank.com/contests/test-practic-pa-2018-v2-cafebabe-101/challenges/test-2-2-1-planificare-medie/problem
class Solution {
    int n,m,p;
    vector<vector<int>> graph;
    vector<int> in_degree;

    public:
        void read() {
            cin >> n >> m >> p;
            n += 1; // 1-indexed
            graph.resize(n);
            in_degree.resize(n, 0);

            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                graph[u].push_back(v);
                in_degree[v]++;
            }


            vector<int> maybe_stop_sort(n, 0);
            while (p) {
                for (int i = 1; i < n; ++i) {
                    cin >> maybe_stop_sort[i];
                }

                if (is_top_sort(maybe_stop_sort)) {
                    cout << "DA" << endl;
                } else {
                    cout << "NU" << endl;
                }
                p--;
                maybe_stop_sort.clear();
                maybe_stop_sort.resize(n, 0);
            }
        }

        void solve() {
            // code here
        }

        bool is_top_sort(vector<int> maybe) {
            // check relative order of elements in maybe
            unordered_map<int, int> position;
            for (int i = 1; i < n; ++i) {
                position[maybe[i]] = i;
            }

            for (int i = 1; i < n; ++i) {
                for (int j = 0; j < graph[i].size(); ++j) {
                    if (position[i] > position[graph[i][j]]) {
                        return false;
                    }
                }
            }

            return true;
        }

        // void top_sort() {
        //     vector<bool> visited(n, false);

        //     queue<int> q;

        //     for (int i = 1; i < n; i++) {
        //         if (in_degree[i] == 0) {
        //             q.push(i);
        //             visited[i] = true;
        //         }
        //     }

        //     while (!q.empty()) {
        //         int u = q.front();
        //         q.pop();

        //         topological_sort.push_back(u);

        //         for (int v : graph[u]) {
        //             in_degree[v]--;
        //             if (in_degree[v] == 0 && !visited[v]) {
        //                 q.push(v);
        //                 visited[v] = true;
        //             }
        //         }
        //     }
        // }

        void print() {
            // code here
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




