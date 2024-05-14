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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v1-deadbeef/challenges/test-1-2-1-ursul-medie/problem
class Solution {
    int n;
    vector<int> maze[3]; // maze with 2 rows and n columns , 1 indexed

    pair<int, int> src = {1,1};
    pair<int, int> dst;

    unordered_map<pair<int,int>, long, pair_hash> distances;
    unordered_set<pair<int,int>, pair_hash> visited;
    public:
        void read() {
            cin >> n;
            maze[1].resize(n+1);
            maze[2].resize(n+1);
            for (int i = 1; i <= 2; i++) {
                for (int j = 1; j <= n; j++) {
                    cin >> maze[i][j];
                    distances[{i,j}] = INF;
                }
            }

            dst = {2, n};
        }

        void solve() {
            int dl[] = {-1, 0, 1, 0};
            int dc[] = {0, 1, 0, -1};

            distances[src] = maze[src.first][src.second];
            // min heap of pairs (distance, pair<int,int>)
            priority_queue<pair<long, pair<int,int>>, vector<pair<long, pair<int,int>>>, greater<pair<long, pair<int,int>>>> pq;
            pq.push({distances[src], src});

            while (!pq.empty()) {
                auto [dist_to_node, node] = pq.top();
                pq.pop();

                if (visited.find(node) != visited.end()) {
                    continue;
                }
                visited.insert(node);

                for (int i = 0; i < 4; i++) {
                    int new_x = node.first + dl[i];
                    int new_y = node.second + dc[i];

                    if (new_x >= 1 && new_x <= 2 && new_y >= 1 && new_y <= n && maze[new_x][new_y] != -1) {
                        long new_dist = dist_to_node + maze[new_x][new_y];
                        if (new_dist < distances[{new_x, new_y}]) {
                            distances[{new_x, new_y}] = new_dist;
                            pq.push({new_dist, {new_x, new_y}});
                        }

                       
                    }
                }
            }



            
        }

        void print() {
            cout << distances[dst] << endl;
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