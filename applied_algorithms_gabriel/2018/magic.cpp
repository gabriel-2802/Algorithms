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
// https://www.hackerrank.com/contests/test-practic-pa-2018-v1-deadbeef/challenges/test-1-1-2-sir-magic-usoara/problem
class Solution {
    string input;
    vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                              'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                              'u', 'v', 'w', 'x', 'y', 'z'};
    public:
        void read() {
            cin >> input;
        }

        void solve() {
            int n = input.size();
            for (int i = 0; i < n; ++i) {
                if (input[i] == '_') {
                    char prev = i > 0 ? input[i - 1] : ' ';
                    char next = i < n - 1 ? input[i + 1] : ' ';
                    input[i] = find_lowest(prev, next);
                }
            }
        }

        char find_lowest(char prev, char next) {
            for (char c : alphabet) {
                if (c != prev && c != next) {
                    return c;
                }
            }

            // should never reach here
            return '?';
        }

        void print() {
            cout << input << endl;
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




