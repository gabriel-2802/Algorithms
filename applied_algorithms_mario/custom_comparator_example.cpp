#include <bits/stdc++.h>

using namespace std;

// Declaring a custom comparator
struct comp {
	// Operator() overloading
	bool operator()(const pair<int, int>& p1,
					const pair<int, int>& p2) const
	{
		// definition
		return p1.second > p2.second; // decreasing order after second element
		// return p1.first < p2.first; // increasing order after first element
	}
};

int main()
{
	// Declaring a set of pairs with comparator
	vector<pair<int, int>> vect;
	vect.push_back({ 1, 2 });
	vect.push_back({ 3, 3 });
	vect.push_back({ 1, 5 });
	vect.push_back({ 7, 2 });

	// Using the custom comparator
	sort(vect.begin(), vect.end(), comp());

	// Displaying the sorted elements
	for (auto i : vect) {
		cout << i.first << " " << i.second << endl;
	}

	return 0;
}
