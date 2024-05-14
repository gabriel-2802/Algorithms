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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v2-cafebabe-101/challenges/test-2-2-2-maxdif-usoara
class Solution {
    int n = 0;
    vector<int> a;
    vector<int> b;

    int min_pos = INF;
    int max_neg = -INF;
    int zeros = 0;

    long long sum_a = 0;
    long long sum_b = 0;
    public:
        void read() {
            cin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                if (x > 0) {
                    a.push_back(x);
                    min_pos = min(min_pos, x);
                } else if (x < 0) {
                    b.push_back(x);
                    max_neg = max(max_neg, x);
                } else {
                    zeros++;
                }
            }
        }

        void solve() {
            if (a.size() == 0) {
                if (zeros == 0) {
                    a.push_back(max_neg);
                    sum_b -= max_neg;
                }
            } else if (b.size() == 0) {
                if (zeros == 0) {
                    b.push_back(min_pos);
                    sum_a -= min_pos;
                }
            }

            for (int x : a) {
                sum_a += x;
            }

            for (int x : b) {
                sum_b += x;
            }
        }

        void print() {

            cout << sum_a - sum_b << endl;
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




