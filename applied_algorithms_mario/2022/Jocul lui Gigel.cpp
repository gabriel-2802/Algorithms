// https://www.hackerrank.com/contests/test-practic-recuperare-2022-90528/challenges/jocul-lui-gigel/problem

#include <bits/stdc++.h>

using namespace std;

int main() {
    
    int n, m;
    cin >> n >> m;

    vector<int> v(n + 1);

    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    } 

    for (int i = 1; i < n; ++i) {
        sum += abs(v[i + 1] - v[i]);
    }

    int diff_1 = INT_MAX;
    int diff_x = INT_MAX;
    for (int i = 1; i < n; ++i) {
        diff_1 = min(diff_1, abs(v[i] - 1) + abs(v[i + 1] - 1) - abs(v[i + 1] - v[i]));
        diff_x = min(diff_x, abs(v[i] - m) + abs(v[i + 1] - m) - abs(v[i + 1] - v[i]));
    }

    diff_1 = min({diff_1, abs(v[1] - 1), abs(v[n] - 1)});
    diff_x = min({diff_x, abs(v[1] - m), abs(v[n] - 1)});
    
    if(*max_element(v.begin(),v.end()) >= m) {
        diff_x = 0;
    }

    cout << sum + diff_1 + diff_x << "\n";

    return 0;
}
