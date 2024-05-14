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

// https://www.hackerrank.com/contests/test-practic-pa-2019-64563/challenges/test-1-1-1-gigel-si-testul-surpriza-usoara/problem
class Solution {
    int n, k;
    vector<int> difficulties;

    vector<int> result;
    public:
        void read() {
            cin >> n >> k;
            difficulties.resize(n);
            for (int i = 0; i < n; i++) {
                cin >> difficulties[i];
            }
        }

        void solve() {
            sort(difficulties.begin(), difficulties.end());

            int min_diff = INF;
            int start_index = 0;

            for (int i = 0; i < n - k + 1; i++) {
                int diff = difficulties[i + k - 1] - difficulties[i];
                if (diff < min_diff) {
                    min_diff = diff;
                    start_index = i;
                }
            }

            result = vector<int>(difficulties.begin() + start_index, difficulties.begin() + start_index + k);
            cout << min_diff << endl;
        }

        void print() {
            for (int i = 0; i < k; i++) {
                cout << result[i] << " ";
            }
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




