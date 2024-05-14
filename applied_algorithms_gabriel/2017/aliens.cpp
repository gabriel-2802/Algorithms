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
#define MOD 666013

// add this to use pair as key in unordered_map and unordered_set
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


// https://www.hackerrank.com/contests/test-practic-pa-2017-v1-plumbus/challenges/test-1-extraterestrii/problem
class Solution {
    int n,m,k;
    unordered_set<int> alphabet;
    unordered_map<int, unordered_set<int>> restrictions;  // restrictions[a] = {b1, b2, ...}

    long long result = 0;
    public:
        void read() {
            cin >> n >> m >> k;

            for (int i = 1; i <= m; ++i) {
                alphabet.insert(i);
            }

            for (int i = 0; i < k; ++i) {
                int a,b;
                cin >> a >> b;

                if (restrictions.find(a) == restrictions.end()) {
                    restrictions[a] = unordered_set<int>();
                }

                restrictions[a].insert(b);
            }
        }

        void solve() {
            vector<int> current(n);
            // dp[i][j] = number of words of length i ending with j
            vector<vector<long long>> dp(n+1, vector<long long>(m+1, 0));

            for (int i = 1; i <= m; ++i) {
                dp[1][i] = 1;
            }

            for (int i = 2; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    for (int k = 1; k <= m; ++k) {
                        if (restrictions.find(j) != restrictions.end() && restrictions[j].find(k) != restrictions[j].end()) {
                            continue;
                        }

                        dp[i][j] += dp[i-1][k];
                        dp[i][j] %= MOD;
                    }
                }
            }

            for (int i = 1; i <= m; ++i) {
                result += dp[n][i];
                result %= MOD;
            }

        }
           
        void print() {
            cout << result << endl;
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