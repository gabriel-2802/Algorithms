#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;
#define INF -1.0

// https://www.hackerrank.com/contests/test-practic-pa-2019-64563/challenges/test-1-2-2-conversie-valutara-medie
class Solution {
    int n, m;
    vector<vector<double>> exchange;

public:
    void read() {
        cin >> n >> m;
        n++; // 1-based index
        exchange = vector<vector<double>>(n, vector<double>(n, INF));

        for (int i = 0; i < m; i++) {
            int a, b;
            double c;
            cin >> a >> b >> c;
            exchange[a][b] = c;
        }

        for (int i = 1; i < n; ++i) {
            exchange[i][i] = 1.0;
        }
    }

    void solve() {
        // Floyd-Warshall algorithm to find the maximum exchange rates
        for (int k = 1; k < n; ++k) {
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (exchange[i][k] != INF && exchange[k][j] != INF) {
                        exchange[i][j] = max(exchange[i][j], exchange[i][k] * exchange[k][j]);
                    }
                }
            }
        }
    }

    void print() {
        cout << fixed << setprecision(10);
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (exchange[i][j] == INF) {
                    cout << -1 << " ";
                } else {
                    cout << exchange[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution solution;
    solution.read();
    solution.solve();
    solution.print();
    return 0;
}
