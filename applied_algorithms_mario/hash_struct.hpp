#include <bits/stdc++.h>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

struct vector_hash {
	template <class T>
	std::size_t operator()(const std::vector<T>& vect) const {
		std::size_t seed = vect.size();
		for (auto& i : vect) {
			seed ^= std::hash<T>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};
