#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool can_work(long long mid, vector<int>& tasks, int k) {
    long long time = 0;

    for (auto task : tasks) {
        if (task > mid) return false;

        if (time + task > mid) {
            k--;
            if (k <= 0) return false;
            time = task;
			continue;
        }

		time += task;
    }

    return true;
}


int main() {
    int n, k;
    cin >> n >> k;
    vector<int> tasks(n + 1);
    long long total_time = 0;

    for (int i = 0; i < n; i++) {
        cin >> tasks[i];
        total_time += tasks[i];
    }

    sort(tasks.begin(), tasks.end());

    long long left = tasks.back();
    long long right = total_time;

    while (left < right) {
        long long mid = (left + right) / 2;
        if (can_work(mid, tasks, k))
            right = mid;
        else
            left = mid + 1;
    }

    cout << left;
    return 0;
}
