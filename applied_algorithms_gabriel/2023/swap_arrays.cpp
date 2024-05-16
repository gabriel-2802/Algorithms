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
    priority_queue<int> max_heap_b;
    priority_queue<int, vector<int>, greater<int>> min_heap_a;
    int n,k;

    int max_sum_a = 0;
    public:
        void read() {
            cin >> n >> k;

            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                min_heap_a.push(x);
                max_sum_a += x;
            }

            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                max_heap_b.push(x);
            }
        }

        void solve() {
            while (true) {
                if (k == 0) {
                    break;
                }

                int min_a = min_heap_a.top();
                int max_b = max_heap_b.top();
                if (max_b <= min_a) {
                    break;
                }

                min_heap_a.pop();
                max_heap_b.pop();

                max_sum_a -= min_a;
                max_sum_a += max_b;

                min_heap_a.push(max_b);
                max_heap_b.push(min_a);
                k--;
            }
        }

        void print() {
            cout << max_sum_a << endl;
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




