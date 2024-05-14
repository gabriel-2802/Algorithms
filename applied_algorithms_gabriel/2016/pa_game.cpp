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


// https://www.hackerrank.com/contests/test-practic-pa-2-malfurion/challenges/game-of-pa/problem
class Solution {
    int n;
    vector<vector<int>> graph;
    vector<int> rewards;
    vector<int> required_power;
    vector<int> in_degree;

    vector<int> topological_order;

    public:
        void read() {
            int m;
            cin >> n >> m;
            n++; // 1 index

            graph.resize(n);
            rewards.resize(n, 0);
            required_power.resize(n, 0);
            in_degree.resize(n, 0);
            
           for (int i = 1; i < n; ++i) {
                cin >> rewards[i];
           }

            for (int i = 1; i < n; ++i) {
                cin >> required_power[i];
            }

            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                graph[u].push_back(v);
                in_degree[v]++;
            }

            // // we need best path in graph so we add dummy node 0
            // for (int i = 1; i < n; i++) {
            //     graph[0].push_back(i);
            //     in_degree[i]++;
            // }
        }

        

        void solve() {
            topological_order = top_sort();

            vector<int> dp(n, -INF);
            vector<int> min_power(n, INF);
            

            for (int node = 1; node < n; node++) {
                dp[node] = rewards[node];
                min_power[node] = required_power[node];
            }

            for (int u : topological_order) {
                for (int v : graph[u]) {
                    int new_reward = dp[u] + rewards[v];
                    int new_power = max(min_power[u], required_power[v]);

                    if (new_reward > dp[v]) {
                        dp[v] = new_reward;
                        min_power[v] = new_power;
                    } else if (new_reward == dp[v] && new_power > min_power[v]) {
                        min_power[v] = new_power;
                    
                    }
                }
            }

            int max_reward = *max_element(dp.begin() + 1, dp.end()); // +1 to skip index 0 if unused
            int min_powerr = INF;

            // Ensure we only consider nodes that contribute to the maximum reward
            for (int i = 1; i < n; i++) {
                if (dp[i] == max_reward && min_power[i] < min_powerr) {
                    min_powerr = min_power[i];
                }
            }

            cout << max_reward << " " << min_powerr << endl;
            
        }

        

        vector<int> top_sort() {
            vector<bool> visited(n, false);

            vector<int> sorted;
            vector<int> in_degree_copy = vector<int>(in_degree);

            queue<int> q;
            

            for (int i = 1; i < n; i++) {
                if (in_degree_copy[i] == 0) {
                    q.push(i);
                }
            }

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                sorted.push_back(u);

                for (int v : graph[u]) {
                    in_degree_copy[v]--;
                    if (in_degree_copy[v] == 0) {
                        q.push(v);
                    }
                }
            }
            return sorted;
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