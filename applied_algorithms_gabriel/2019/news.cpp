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
    int n;
    vector<vector<int>> friendships;

    vector<int> discovery_time;
    int max_time = 0;
    public:
        void read() {
            cin >> n;
            n++;
            int m;
            cin >> m;
            friendships.resize(n);
            for (int i = 0; i < m; i++) {
                int a, b;
                cin >> a >> b;
                friendships[a].push_back(b);
                friendships[b].push_back(a);
            }
        }

        void solve() {
            discovery_time.resize(n, -1);

            queue<int> q;
            q.push(1);
            discovery_time[1] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int fr : friendships[node]) {
                    if (discovery_time[fr] == -1) {
                        discovery_time[fr] = discovery_time[node] + 1;
                        max_time = max(max_time, discovery_time[fr]);
                        q.push(fr);
                    }
                   
                }
            }
        }

        void print() {
            cout << max_time << endl;
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




