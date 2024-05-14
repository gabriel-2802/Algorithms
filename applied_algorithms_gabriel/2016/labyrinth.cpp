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


// https://www.hackerrank.com/contests/test-practic-pa-2-malfurion/challenges/labirint-usoara/problem
// 90% score
class Solution {
    int n; // rows
    int m; // columns
    vector<vector<char>> maze;
    unordered_set<pair<int,int>, pair_hash> visited;
    unordered_set<pair<int,int>, pair_hash> portals;
    
    pair<int, int> src;
    pair<int, int> dst;
    
    vector<vector<int>> distances;
    int moves = -1;

    public:
        void read() {
            cin >> n >> m;
            maze = vector<vector<char>>(n, vector<char>(m));
            distances = vector<vector<int>>(n, vector<int>(m, -1));

           

            string line;
            for (int i = 0; i < n; i++) {
                cin >> line;
                for (int j = 0; j < m; j++) {
                    maze[i][j] = line[j];
                    if (maze[i][j] == 'P') {
                        portals.insert({i,j});
                    }
                    if (maze[i][j] == 'S') {
                        src = {i,j};
                    }

                    if (maze[i][j] == 'D') {
                        dst = {i,j};
                    }

                }
            }
        }

        void solve() {
            int dl[] = {-1, 0, 1, 0};
            int dc[] = {0, 1, 0, -1};

            queue<pair<int,int>> q;
            q.push(src);
            visited.insert(src);
            distances[src.first][src.second] = 0;

            while (!q.empty()) {
                auto point = q.front();
                int x = point.first;
                int y = point.second;
                q.pop();

                for (int i = 0; i < 4; i++) {
                    int new_x = x + dl[i];
                    int new_y = y + dc[i];

                    if (valid(new_x, new_y) && visited.find({new_x, new_y}) == visited.end()) {
                        visited.insert({new_x, new_y});
                        q.push({new_x, new_y});
                        distances[new_x][new_y] = distances[x][y] + 1;

                        if (new_x == dst.first && new_y == dst.second) {
                            moves = distances[new_x][new_y];
                            return;
                        }

                        if (is_portal(new_x, new_y)) {
                            for (auto portal : portals) {
                                if (portal != make_pair(new_x, new_y) && visited.find(portal) == visited.end()) {
                                    visited.insert(portal);

                                    q.push(portal);
                                    distances[portal.first][portal.second] = distances[new_x][new_y];
                                }
                            }
                        }
                    }
                }
            }
}

        bool is_portal(int x, int y) {
            return portals.find({x,y}) != portals.end();
        }

        bool valid(int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != 'X';
        }

        void print() {
            cout << moves << endl;
        }
};

int main() {
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}