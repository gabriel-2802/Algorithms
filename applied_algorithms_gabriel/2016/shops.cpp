#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <unordered_set>
#include <functional>
#include <algorithm>

using namespace std;

// add this to use pair as key in unordered_map and unordered_set
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

// https://www.hackerrank.com/contests/test-practic-pa-2-malfurion/challenges/magazine-problema-medie/problem
// 70% score
class Solution {
    int n, m;
    vector<vector<pair<int, int>>> intersections; // src -> {dst, distance}
    unordered_set<int> shops;
    vector<int> homes;
    unordered_map<int, int> closest_shop; // home -> closest shop distance
    unordered_map<int, int> closest_shop_id; // home -> closest shop id

    public:
        void read() {
            cin >> n >> m;
            intersections = vector<vector<pair<int, int>>>(n + 1);

            for (int i = 0; i < m; ++i) {
                int src, dest, cost;
                cin >> src >> dest >> cost;
                intersections[src].push_back({dest, cost});
                intersections[dest].push_back({src, cost});
            }

            int s, h;
            cin >> h >> s;

            for (int i = 0; i < h; ++i) {
                int home;
                cin >> home;
                homes.push_back(home);
                closest_shop[home] = numeric_limits<int>::max();
                closest_shop_id[home] = 0;
            }

            for (int i = 0; i < s; ++i) {
                int shop;
                cin >> shop;
                shops.insert(shop);
            }
        }

        pair<vector<int>, vector<int>> dijkstra(int src) {
            int v = n + 1; // 1-indexed

            vector<int> parent = vector<int>(v, -1);
            vector<int> distance = vector<int>(v, numeric_limits<int>::max());
            vector<bool> visited = vector<bool>(v, false);

            distance[src] = 0;

            // min heap based on cost
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, src});

            while (!pq.empty()) {
                auto cost_node = pq.top();
                pq.pop();
                int dist_to_node = cost_node.first;
                int node = cost_node.second;

                if (visited[node]) {
                    continue;
                }
                visited[node] = true;

                for (auto edge : intersections[node]) {
                    int neighbor = edge.first;
                    int cost = edge.second;

                    if (distance[neighbor] > dist_to_node + cost) {
                        distance[neighbor] = dist_to_node + cost;
                        parent[neighbor] = node;
                        pq.push({distance[neighbor], neighbor});
                    }
                }
            }

            return {distance, parent};
        }



        void solve() {
            // find shortest path from each home to a shop
            for (int shop : shops) {
                auto dist_parent = dijkstra(shop);
                vector<int> distance = dist_parent.first;

                for (int home : homes) {
                    if (distance[home] < closest_shop[home]) {
                        closest_shop[home] = distance[home];
                        closest_shop_id[home] = shop;
                    }
                }
            }

        }

        void print() {
            
            for (int home : homes) {
                cout << closest_shop_id[home] << " ";
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