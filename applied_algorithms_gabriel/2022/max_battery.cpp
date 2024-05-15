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
    vector<int> times; // only for important meetings
    int x;

    long battery = 0;
    public:
        void read() {
            cin >> n;
            for (int i = 0; i < n; ++i) {
                int imp, time;
                cin >> imp >> time;
                if (imp == 1) {
                    times.push_back(time);
                } else {
                    battery += time;
                }
            }

            cin >> x;
        }

        void solve() {
            sort(times.begin(), times.end(), greater<int>());
            for (int i = 0; i < times.size(); ++i) {
                if (x > 0) {
                    battery += times[i];
                    x--;
                } else {
                    battery -= times[i];
                }
            }
        }

        void print() {
            cout << battery << endl;
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




