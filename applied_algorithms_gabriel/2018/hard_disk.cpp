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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v2-cafebabe-101/challenges/test-2-1-1-hard-disk-usoara
class Solution {
    int n,d;
    vector<int> sectors;

    int distance = 0;
    public:
        void read() {
            cin >> n >> d;
            sectors.resize(d);
            for (int i = 0; i < d; i++) {
                int sector;
                cin >> sector;
                sectors[i] = sector;
            }
        }

        void solve() {
            sort(sectors.begin(), sectors.end());
            int max_diff = 0;
            for (int i = 1; i < d; i++) {
                max_diff = max(max_diff, sectors[i] - sectors[i - 1]);
            }
            max_diff = max(max_diff, n - sectors[d - 1] + sectors[0]);
            // basically, we need to find the maximum distance between two sectors
            // and then subtract it from the total distance since it will be only distance
            // that we will not cover
            distance = n - max_diff;
        } 

        void print() {
            cout << distance << endl;
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




