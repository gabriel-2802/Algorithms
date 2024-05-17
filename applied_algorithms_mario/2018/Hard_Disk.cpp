#include <bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int d, n;
	cin >> d >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];


	sort(arr.begin(), arr.end());

	return 0;
}

/*

9 3
1 4 7



7 3
1  4  7
  3  4

*/