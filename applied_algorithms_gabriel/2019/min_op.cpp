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

// https://www.hackerrank.com/contests/test-practic-pa-2019-64563/challenges/test-1-2-1-numar-minim-de-operatii-medie
class Solution {
    int n;
    vector<int> values;
    int src, dest;

    int operations = 0;
    public:
        void read() {
            cin >> n;
            values.resize(n);
            for (int i = 0; i < n; i++) {
                cin >> values[i];
            }

            cin >> src >> dest;
        }

        void solve() {
            // bfs
            queue<pair<int,int>> q; // node, operations
            unordered_set<int> visited;

            q.push({src, 0});
            visited.insert(src);

            while (!q.empty()) {
                auto [node, ops] = q.front();
                q.pop();

                if (node == dest) {
                    operations = ops;
                    break;
                }

                for (int num : values) {
                    int next_plus = node + num;
                    int next_minus = node - num;

                    if (!visited.count(next_plus)) {
                        visited.insert(next_plus);
                        q.push({next_plus, ops + 1});
                    }

                    if (!visited.count(next_minus)) {
                        visited.insert(next_minus);
                        q.push({next_minus, ops + 1});
                    }
                }
                
            }


        }

        void print() {
           cout << operations << endl;
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




