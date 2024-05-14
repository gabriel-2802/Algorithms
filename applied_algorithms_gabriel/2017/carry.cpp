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

// https://www.hackerrank.com/contests/test-practic-pa-2017-v1-plumbus/challenges/1-2-usoare/problem
class Solution {
    vector<int> boxes;
    int trips, n;
    int total_weight = 0;
    int minimum_weight = -INF;

    int minimum_strength = -INF;
    public:
        void read() {
            cin >> n >> trips;
            boxes = vector<int>(n);
            for (int i = 0; i < n; i++) {
                cin >> boxes[i];
                total_weight += boxes[i];
                minimum_weight = max(minimum_weight, boxes[i]);
            }
        }

    bool canCarry(int strength) {
        long long currentLoad = 0;
        int requiredTrips = 1;
        
        for (int weight : boxes) {
            if (currentLoad + weight > strength) {
                ++requiredTrips;
                currentLoad = weight;
                if (requiredTrips > trips) {
                    return false;
                }
            } else {
                currentLoad += weight;
            }
        }
        
        return true;
    }

    void solve() {
        long long left = minimum_weight, right = total_weight;
        
        while (left < right) {
            long long mid = (left + right) / 2;
            if (canCarry(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        minimum_strength = left; // The smallest valid strength
    }

        void print() {
            cout << minimum_strength << endl;
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