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


// https://www.hackerrank.com/contests/test-practic-pa-2017-v1-plumbus/challenges/1-1-usoare/problem
class Solution {
    // min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int n, k;
    int max_sum = 0;
    public:
        void read() {
            cin >> n >> k;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                minHeap.push(x);
            }
        }

        void solve() {
            while (k--) {
                int x = minHeap.top();
                minHeap.pop();
                minHeap.push(x * (-1));
            }

            while (!minHeap.empty()) {
                max_sum += minHeap.top();
                minHeap.pop();
            }
        }

        void print() {
            cout << max_sum << endl;
        }
};

// add this to use pair as key in unordered_map and unordered_set
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


int main() {
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}