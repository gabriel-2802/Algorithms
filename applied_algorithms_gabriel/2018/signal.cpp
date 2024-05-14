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

// https://www.hackerrank.com/contests/test-practic-pa-2018-v1-deadbeef/challenges/test-1-1-1-semnal-usoara/problem
class Solution {
    int n;
    vector<int> values;
    int ones = 0;

    int min_res = 0;
    public:
        void read() {
            cin >> n;
            values.resize(n);
            for (int i = 0; i < n; i++) {
                cin >> values[i];
                if (values[i] == 1) {
                    ones++;
                }
            }
        }

        void solve() {
           for (int i = 0; i < n; ++i) {
                if (values[i] == 1) {
                    i += 2;
                    min_res++;
                }
           }
        }

        void print() {
            cout << min_res << " " << ones << endl;
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
    std::ios::sync_with_stdio(false);  
    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}