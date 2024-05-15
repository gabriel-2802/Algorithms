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
#include <cmath>

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
    vector<double> a;
    int cardinal = 0;

    double total_sum = 0;
    public:
        void read() {
            cin >> n;
            a.resize(n);
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                a[i] = log(x);
                total_sum += a[i];
            }
        }

        void solve() {
            double curr_sum = 0;
            sort(a.begin(), a.end(), greater<double>());

            int index = 0;
            while (curr_sum < total_sum) {
                curr_sum += a[index];
                total_sum -= a[index];
                index++;
                cardinal++;
            }
        }

        void print() {
            cout << cardinal << endl;
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




