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

// https://www.hackerrank.com/contests/test-practic-pa-2019-64563/challenges/test-1-1-2-generare-siruri/problem
class Solution {
    int n;
    public:
        void read() {
            cin >> n;
            if (n == 0) {
                cout <<  -1 << endl;
                exit(0);
            }
        }

        void special_permutations(vector<int>&current, vector<bool>& used, int k) {
            if (current.size() == n) {
                for (int i = 0; i < n; i++) {
                    cout << current[i] << " ";
                }
                cout << endl;
                return;
            }

            int prev = current[k-1];
            for (int i = 1; i <= n; ++i) {
                if (!used[i] && (i % 2 != prev % 2)) {
                    current.push_back(i);
                    used[i] = true;
                    special_permutations(current, used, k+1);
                    current.pop_back();
                    used[i] = false;
                }
            }
        }

        void solve() {
            vector<int> current;
            vector<bool> used(n+1, false);
            for (int i = 1; i <= n; i++) {
                current.push_back(i);
                used[i] = true;
                special_permutations(current, used, 1);
                current.pop_back();
                used[i] = false;
            }
        }

        void print() {
            
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




